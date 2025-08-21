/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_universal(
        'L', 'L', 'L', 'L', 'L', 'L',                     'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',                     'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',                     'R', 'R', 'R', 'R', 'R', 'R',
                   'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R'
    );

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0: Base layer (QWERTY)
    [0] = LAYOUT_universal(
        KC_ESC,         KC_Q,     KC_W,     KC_E,         KC_R,         KC_T,                                      KC_Y,     KC_U,         KC_I,         KC_O,     KC_P,     KC_BSLS,
        LCTL_T(KC_TAB), KC_A,     KC_S,     LALT_T(KC_D), LGUI_T(KC_F), KC_G,                                      KC_H,     RGUI_T(KC_J), LALT_T(KC_K), KC_L,     KC_SCLN,  RCTL_T(KC_QUOT),
        KC_LSFT,        KC_Z,     KC_X,     KC_C,         KC_V,         KC_B,                                      KC_N,     KC_M,         KC_COMM,      KC_DOT,   KC_SLSH,  KC_RSFT,
                                  KC_LALT,  KC_LGUI,      MO(4),        TL_LOWR,   LT(3,KC_SPC),         KC_ENT,   TL_UPPR,  _______,      _______,      KC_PSCR
    ),

    // Layer 1: Symbols & Navigation
    [1] = LAYOUT_universal(
        KC_GRV,         S(KC_1),  S(KC_2),  S(KC_3),      S(KC_4),      S(KC_5),                                   S(KC_6),  S(KC_7),      S(KC_8),      S(KC_9),  S(KC_0),  KC_BSPC,
        _______,        _______,  _______,  _______,      _______,      _______,                                   KC_LEFT,  KC_LCBR,      KC_RCBR,      KC_LBRC,  KC_RBRC,  KC_F12,
        _______,        KC_EQL,   KC_MINS,  KC_PLUS,      _______,      _______,                                   _______,  _______,      _______,      KC_LPRN,  KC_RPRN,  _______,
                                  _______,  _______,      _______,      _______,   _______,              KC_BSPC,  _______,  _______,      _______,      _______
    ),

    // Layer 2: Numbers & Arrows
    [2] = LAYOUT_universal(
        KC_TILD,        KC_1,       KC_2,     KC_3,         KC_4,         KC_5,                                    KC_6,       KC_7,         KC_8,     KC_9,       KC_0,       KC_BSPC,
        _______,        S(KC_SCLN), KC_4,     KC_5,         KC_6,         KC_RBRC,                                 KC_LEFT,    KC_DOWN,      KC_UP,    KC_RIGHT,   KC_QUOT,    S(KC_2),
        _______,        S(KC_MINS), KC_1,     KC_2,         KC_3,         S(KC_RBRC),                              S(KC_NUHS), S(KC_INT1),   KC_EQL,   S(KC_LBRC), S(KC_SLSH), S(KC_INT3),
                                    KC_0,     KC_DOT,       _______,      _______,   _______,            KC_DEL,   _______,    _______,      _______,  _______
    ),

    // Layer 3: RGB & Mouse controls
    [3] = LAYOUT_universal(
        _______,        AML_TO,   AML_I50,  AML_D50,      _______,      _______,                                   _______,  _______,      _______,      _______,  _______,  _______,
        _______,        _______,  _______,  _______,      _______,      SCRL_DVI,                                  _______,  _______,      _______,      _______,  _______,  _______,
        _______,        _______,  _______,  _______,      _______,      SCRL_DVD,                                  CPI_D1K,  CPI_D100,     CPI_I100,     CPI_I1K,  _______,  KBC_SAVE,
                                  QK_BOOT,  KBC_RST,      _______,      _______,   _______,              _______,  _______,   _______,     KBC_RST,      QK_BOOT
    ),

    // Layer 4: Mouse buttons
    [4] = LAYOUT_universal(
        _______,        _______,  _______,  _______,      _______,      _______,                                   _______,  _______,      _______,      _______,  _______,  _______,
        _______,        _______,  _______,  _______,      _______,      _______,                                   _______,  KC_BTN1,      KC_BTN2,      KC_BTN3,  _______,  _______,
        _______,        _______,  _______,  _______,      _______,      _______,                                   _______,  _______,      _______,      _______,  _______,  _______,
                                  _______,  _______,      _______,      _______,   _______,              _______,  _______,  _______,      _______,      _______
    ),

    // Layer 5: Media
    [5] = LAYOUT_universal(
        _______,        _______,  _______,  _______,      _______,      _______,                                   _______,  KC_VOLD,      KC_MUTE,      KC_VOLU,  _______,  _______,
        _______,        _______,  _______,  _______,      _______,      _______,                                   _______,  KC_MPRV,      KC_MPLY,      KC_MNXT,  _______,  _______,
        _______,        _______,  _______,  _______,      _______,      _______,                                   _______,  _______,      _______,      _______,  _______,  _______,
                                  _______,  _______,      _______,      _______,   _______,              _______,  _______,  _______,      _______,      _______
    ),
};
// clang-format on

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    if (tap_hold_keycode == LCTL_T(KC_TAB)) {
        // Hold for all keys as it is very high change that what I want is
        // <C-<other_keycode>>.
        return true;
    }

    if (tap_hold_keycode == RCTL_T(KC_QUOT)) {
        switch (other_keycode) {
            case KC_B: // <C-b> ghostty prefix.
            case KC_C: // <C-c>
                return true;
        }
        return true;
    }

    return get_chordal_hold_default(tap_hold_record, other_record);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LCTL_T(KC_TAB):
        case LCTL_T(KC_QUOT):
            return TAPPING_TERM - 40;
    }

    return TAPPING_TERM;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
