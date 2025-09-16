use anyhow::{Context, Result};
use hidapi::{HidApi, HidDevice};
use log::{debug, error, info, warn};
use serde::Serialize;
use std::fs;
use std::io::Write;
use std::os::unix::net::{UnixListener, UnixStream};
use std::sync::{Arc, Mutex};
use std::thread;
use std::time::{Duration, Instant};

// Keyball44
const VENDOR_ID: u16 = 0x5957;
const PRODUCT_ID: u16 = 0x0400;
const USAGE_PAGE: u16 = 0xFF60;
const USAGE: u16 = 0x61;
const PACKET_SIZE: usize = 32;

#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq)]
enum HidCommand {
    LayerStatus = 0x01,
}

#[derive(Debug, Clone, Serialize)]
pub struct LayerStatus {
    #[serde(rename = "name")]
    pub layer_name: String,
    #[serde(rename = "id")]
    pub layer_id: u8,
    #[serde(rename = "state")]
    pub layer_state: u32,
    pub timestamp: u64,
}

fn layer_name(id: u8) -> &'static str {
    match id {
        0 => "QWERTY",    // Base layer
        1 => "SYMBOLS",   // Symbols & Navigation
        2 => "NUMBERS",   // Numbers & Arrows
        3 => "MOUSE_CTL", // RGB & Mouse controls
        4 => "MOUSE_BTN", // Mouse buttons
        5 => "MEDIA",     // Media, miscellaneous
        _ => "UNKNOWN",
    }
}

struct SocketServer {
    clients: Arc<Mutex<Vec<UnixStream>>>,
    socket_path: String,
}

impl SocketServer {
    fn new() -> Result<Self> {
        let socket_path = format!("/tmp/qmk-layer-monitor.sock");

        let _ = fs::remove_file(&socket_path);

        let server = Self {
            clients: Arc::new(Mutex::new(Vec::new())),
            socket_path,
        };

        Ok(server)
    }

    fn start(&self) -> Result<()> {
        let listener =
            UnixListener::bind(&self.socket_path).context("Failed to bind Unix socket")?;

        info!("Unix socket server listening on: {}", self.socket_path);

        let clients = Arc::clone(&self.clients);
        thread::spawn(move || {
            for stream in listener.incoming() {
                match stream {
                    Ok(stream) => {
                        info!("New client connected");
                        let mut clients = clients.lock().unwrap();
                        clients.push(stream);
                    }
                    Err(e) => {
                        error!("Failed to accept connection: {}", e);
                    }
                }
            }
        });

        Ok(())
    }

    fn broadcast(&self, message: &str) {
        let mut clients = self.clients.lock().unwrap();
        clients.retain_mut(|client| match writeln!(client, "{}", message) {
            Ok(_) => {
                debug!("Sent to client: {}", message);
                true
            }
            Err(_) => {
                debug!("Client disconnected");
                false
            }
        });
    }
}

impl Drop for SocketServer {
    fn drop(&mut self) {
        let _ = fs::remove_file(&self.socket_path);
    }
}

struct QmkMonitor {
    device: Option<HidDevice>,
    last_reconnect: Instant,
    socket_server: SocketServer,
    last_layer_id: Option<u8>,
}

impl QmkMonitor {
    fn new() -> Result<Self> {
        let socket_server = SocketServer::new()?;
        socket_server.start()?;

        Ok(Self {
            device: None,
            last_reconnect: Instant::now(),
            socket_server,
            last_layer_id: None,
        })
    }

    fn connect(&mut self) -> Result<()> {
        let api = HidApi::new().context("Failed to initialize HID API")?;

        let device_info = api
            .device_list()
            .find(|d| {
                d.vendor_id() == VENDOR_ID
                    && d.product_id() == PRODUCT_ID
                    && d.usage_page() == USAGE_PAGE
                    && d.usage() == USAGE
            })
            .context(format!(
                "Keyball44 RAW HID interface not found (VID: 0x{:04x}, PID: 0x{:04x})",
                VENDOR_ID, PRODUCT_ID
            ))?;

        let device = device_info
            .open_device(&api)
            .context("Failed to open HID device")?;

        device
            .set_blocking_mode(false)
            .context("Failed to set non-blocking mode")?;

        info!("Connected to Keyball44!");
        self.device = Some(device);
        Ok(())
    }

    fn process_packet(&mut self, buffer: &[u8]) -> Result<()> {
        if buffer.len() < 4 {
            return Ok(());
        }

        if buffer[0] != HidCommand::LayerStatus as u8 {
            return Ok(());
        }

        let layer_id = buffer[1];
        let layer_state = u32::from_le_bytes([buffer[2], buffer[3], 0, 0]);

        if Some(layer_id) == self.last_layer_id {
            return Ok(());
        }

        let status = LayerStatus {
            layer_name: layer_name(layer_id).to_string(),
            layer_id,
            layer_state,
            timestamp: std::time::SystemTime::now()
                .duration_since(std::time::UNIX_EPOCH)?
                .as_secs(),
        };

        debug!(
            "Layer: {} ({}), State: 0x{:04x}",
            status.layer_name, layer_id, layer_state
        );

        let json = serde_json::to_string(&status)?;
        self.socket_server.broadcast(&json);

        self.last_layer_id = Some(layer_id);

        Ok(())
    }

    fn run(&mut self) -> Result<()> {
        info!("Starting QMK layer monitor...");
        info!(
            "Listening for HID command: LayerStatus (0x{:02x})",
            HidCommand::LayerStatus as u8
        );

        let mut buffer = [0u8; PACKET_SIZE];

        loop {
            if self.device.is_none() {
                if self.last_reconnect.elapsed() > Duration::from_secs(3) {
                    match self.connect() {
                        Ok(()) => {
                            info!("Connected successfully!");
                        }
                        Err(e) => {
                            warn!("Connection failed: {}", e);
                            self.last_reconnect = Instant::now();
                        }
                    }
                } else {
                    std::thread::sleep(Duration::from_millis(100));
                    continue;
                }
            }

            if let Some(ref mut device) = self.device {
                match device.read_timeout(&mut buffer, 100) {
                    Ok(PACKET_SIZE) => {
                        if let Err(e) = self.process_packet(&buffer) {
                            error!("Error processing packet: {}", e);
                        }
                    }
                    Ok(0) => {}
                    Ok(n) => warn!("Received partial packet: {} bytes", n),
                    Err(e) => {
                        error!("Read error: {}", e);
                        self.device = None;
                        self.last_reconnect = Instant::now();
                    }
                }
            }

            std::thread::sleep(Duration::from_millis(10));
        }
    }
}

fn main() -> Result<()> {
    env_logger::Builder::from_env(env_logger::Env::default().default_filter_or("info")).init();

    let mut monitor = QmkMonitor::new()?;

    ctrlc::set_handler(move || {
        info!("Received Ctrl+C, exiting...");
        std::process::exit(0);
    })
    .expect("Error setting Ctrl+C handler");

    monitor.run()
}
