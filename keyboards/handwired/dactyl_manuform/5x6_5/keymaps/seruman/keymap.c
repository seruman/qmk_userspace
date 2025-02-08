// Copyright 2021 Christian Eiden, cykedev
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#define CM_SPAL  LGUI_T(KC_SPC)
#define CM_SPAR  RGUI_T(KC_SPC)

#define SH_LCTL LSFT_T(KC_LALT)
#define SH_RCTL RSFT_T(KC_RALT)

#define LWR     MO(_LOWER)
#define RAI     MO(_RAISE)
#define ADJ     MO(_ADJUST)

#define QWERT   DF(_QWERTY)

enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6_5(
  /* QWERTY
   * .-----------------------------------------.                                  .-----------------------------------------.
   * | Esc  |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  Bsp |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * | Shft |   Z  |   X  |   C  |   V  |   B  |                                  |   N  |   M  |   ,  |   .  |   /  | Shft |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |  ADJ |  ALT |    /  Cmd  /---------------.    .---------------\  Cmd  \    |  ALT | ADJ  |
   *               |      |      |   /       /  LWR  / Shift /      \ Shift \  RAI  \       \   |      |      |
   *               '-------------'  '-------/       / Ctrl  /        \ Ctrl  \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      / Space / Enter /            \  Enter\ Space \
   *                                     /       /       /              \       \       \
   *                                    '---------------'                '---------------'
   */
   QK_GESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
   KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                                     KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                     ADJ    , KC_LALT,          KC_LGUI, LWR    , SH_LCTL, SH_RCTL, RAI    , KC_RGUI,          KC_RALT, ADJ    ,
                                                         KC_SPC , KC_ENT , KC_ENT , KC_SPC 
   ),
  [_LOWER] = LAYOUT_5x6_5(
  /* LOWER
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  -   |  =   |  F11 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |                                  |   6  |  {   |   }  |  [   |  ]   |  F12 |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |   !  |   @  |   #  |   $  |   %  |                                  |   ^  |   &  |  *   |  (   |  )   |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |   =  |   -  |   +  |   {  |   }  |                                  |   [  |   ]  |   ;  |  :   |  \   |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    /       /---------------.    .---------------\       \    |      |      |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       /       /            \       \       \
   *                                     /       /       /              \       \       \
   *                                    '---------------'                '---------------'
   */
   KC_GRV , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                     KC_F6  , KC_F7  , KC_F8  , KC_MINS, KC_EQL , KC_F11 ,
   XXXXXXX, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                     KC_6   , KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_F12 ,
   _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
   _______, KC_EQL , KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR,                                     KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                     _______, _______,          _______, _______, _______, _______, _______, _______,          _______, _______,
                                                         _______, _______, _______, _______
   ),
  [_RAISE] = LAYOUT_5x6_5(
  /* RAISE
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |                                  | left | down | up   | right|      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    /       /---------------.    .---------------\       \    |      |      |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       /       /            \       \       \
   *                                     /       /       /              \       \       \
   *                                    '---------------'                '---------------'
   */
   _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
   _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
                     _______, _______,          _______, _______, _______, _______, _______, _______,          _______, _______,
                                                         _______, _______, _______, _______
   ),
  [_ADJUST] = LAYOUT_5x6_5(
  /* ADJUST
   * .-----------------------------------------.                                  .-----------------------------------------.
   * |  RST |      |      |      |      | QWERT|                                  |      |      |      |      |      | RST  |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |                                  |      | VOLDO| MUTE | VOLUP|      |      |
   * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
   * |      |      |      |      |      |      |                                  |      | PREV | PLAY | NEXT |      |      |
   * '-----------------------------------------/                                  \-----------------------------------------'
   *               |      |      |    /       /---------------.    .---------------\       \    |      |      |
   *               |      |      |   /       /       /       /      \       \       \       \   |      |      |
   *               '-------------'  '-------/       /       /        \       \       \-------'  '-------------'
   *                                       /---------------/          \---------------\
   *                                      /       /       /            \       \       \
   *                                     /       /       /              \       \       \
   *                                    '---------------'                '---------------'
   */
   QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QWERT  ,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                     _______, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, _______,
                                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
   )
};

