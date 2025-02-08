// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "features/achordion.h"

enum layer_names {
  _BASE,
  _LOWER,
  _DOUBLE_LOWER,
  _RAISE,
  _DOUBLE_RAISE,
  _ADJUST,
};

enum tap_dance_codes {
  TD_LOWER = 0,
  TD_RAISE,
};

typedef struct {
  bool is_press_action;
  int state;
} xtap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, // send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  UNKNOWN = 99

};

#define LOWER TD(TD_LOWER)
#define RAISE TD(TD_RAISE)
#define ADJUST MO(_ADJUST)

#define Z_LSFT LSFT_T(KC_Z)
#define SLSH_RSFT RSFT_T(KC_SLSH)
#define EQL_LSFT LSFT_T(KC_EQL)
#define RBRC_RSFT RSFT_T(KC_RBRC)

#define SCLN_CTL RCTL_T(KC_SCLN)
#define A_CTL LCTL_T(KC_A)
#define J_GUI LGUI_T(KC_J)
#define G_GUI LGUI_T(KC_G)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *     BASE
     *
     *             ┌───┐                            ┌───┐
     *         ┌───┤ E ├───┐                    ┌───┤ I ├───┐
     *     ┌───┤ W ├───┤ R ├───┐            ┌───┤ U ├───┤ O ├───┐
     *     │ Q ├───┤ F ├───┤ T │            │ Y ├───┤ K ├───┤ P │
     *     ├───┤ D ├───┤ G ├───┤            ├───┤ J ├───┤ L ├───┤
     *     │ A ├───┤ C ├───┤ H │            │ H ├───┤ , ├───┤ ; │
     *     ├SFT┤ X ├───┤ V ├───┤            ├───┤ N ├───┤ . ├SFT┤
     *     │ Z ├───┘   └───┤ B │            │ M ├───┘   └───┤ / │ <--- TODO(selman): RSFT_T(KC_SLSH)
     *     └───┘           └───┘            └───┘           └───┘
     *                 ┌GUI┐                    ┌GUI┐
     *                 │CTL├───┐            ┌───┤CTL│
     *                 └───┤LWR├───┐    ┌───┤RAI├───┘
     *                     └───┤   │    │   ├───┘
     *                         │SPC│    │ENT│
     *                         │   │    │   │
     *                         └───┘    └───┘
     *
     */
    [_BASE] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        A_CTL,   KC_S,    KC_D,    KC_F,    G_GUI,                              KC_H,    G_GUI,   KC_K,    KC_L,    SCLN_CTL,
        Z_LSFT,  KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  SLSH_RSFT,
                                   KC_RGUI, LOWER,   KC_SPC,           KC_ENT,  RAISE,   KC_LGUI
    ),

    /*
     * LOWER
     *
     *         ┌───┐                            ┌───┐
     *     ┌───┤ 3 ├───┐                    ┌───┤ 8 ├───┐
     * ┌───┤ 2 ├───┤ 4 ├───┐            ┌───┤ 7 ├───┤ 9 ├───┐
     * │ 1 ├───┤ # ├───┤ 5 │            │ 6 ├───┤ * ├───┤ 0 │
     * ├───┤ @ ├───┤ $ ├───┤            ├───┤ & ├───┤ ( ├───┤
     * │ ! ├───┤ + ├───┤ % │            │ ^ ├───┤ } ├───┤ ) │
     * ├SFT┤ - ├───┤ _ ├───┤            ├───┤ { ├───┤ [ ├SFT┤
     * │ = ├───┘   └───┤ ` │            │ \ ├───┘   └───┤ ] │
     * └───┘           └───┘            └───┘           └───┘
     *             ┌───┐                    ┌───┐
     *             │   ├───┐            ┌───┤   │
     *             └───┤   ├───┐    ┌───┤   ├───┘
     *                 └───┤   │    │   ├───┘
     *                     │   │    │BSP│
     *                     │   │    │   │
     *                     └───┘    └───┘
     *
     */

    [_LOWER] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        EQL_LSFT,KC_MINS, KC_PLUS, KC_UNDS, KC_GRV,                             KC_BSLS, KC_LCBR, KC_RCBR, KC_LBRC, RBRC_RSFT,
                                   _______, _______, _______,          KC_BSPC, _______, _______
    ),


    /*
     * DOUBLE LOWER
     *
     *         ┌───┐                            ┌───┐
     *     ┌───┤   ├───┐                    ┌───┤   ├───┐
     * ┌───┤   ├───┤   ├───┐            ┌───┤   ├───┤   ├───┐
     * │B*T├───┤   ├───┤   │            │   ├───┤   ├───┤BSP│
     * ├───┤   ├───┤   ├───┤            ├───┤   ├───┤   ├───┤
     * │   ├───┤   ├───┤   │            │   ├───┤   ├───┤   │
     * ├───┤   ├───┤   ├───┤            ├───┤   ├───┤   ├───┤
     * │   ├───┘   └───┤   │            │   ├───┘   └───┤   │
     * └───┘           └───┘            └───┘           └───┘
     *             ┌───┐                    ┌───┐
     *             │   ├───┐            ┌───┤   │
     *             └───┤   ├───┐    ┌───┤   ├───┘
     *                 └───┤   │    │   ├───┘
     *                     │   │    │   │
     *                     │   │    │   │
     *                     └───┘    └───┘
     *
     */

    [_DOUBLE_LOWER] = LAYOUT_split_3x5_3(
        QK_BOOT, _______, _______, _______, _______,                            _______, _______, _______, _______, KC_BSPC,
        _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,
                                   _______, _______, _______,          _______, _______, _______
    ),

    /*
     * RAISE
     *
     *         ┌───┐                            ┌───┐
     *     ┌───┤   ├───┐                    ┌───┤   ├───┐
     * ┌─~─┤   ├───┤   ├───┐            ┌───┤   ├───┤   ├───┐
     * │ESC├───┤   ├───┤B*T│            │   ├───┤UP ├───┤   │
     * ├───┤   ├───┤   ├───┤            ├───┤DWN├───┤RGT├───┤
     * │TAB├───┤   ├───┤   │            │LFT├───┤   ├───┤ ' │
     * ├───┤   ├───┤   ├───┤            ├───┤   ├───┤   ├───┤
     * │   ├───┘   └───┤   │            │   ├───┘   └───┤   │
     * └───┘           └───┘            └───┘           └───┘
     *             ┌───┐                    ┌───┐
     *             │   ├───┐            ┌───┤   │
     *             └───┤   ├───┐    ┌───┤   ├───┘
     *                 └───┤   │    │   ├───┘
     *                     │   │    │   │
     *                     │   │    │   │
     *                     └───┘    └───┘
     *
     */

    [_RAISE] = LAYOUT_split_3x5_3(
        QK_GESC, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,
        KC_TAB,  _______, _______, _______, _______,                            KC_LEFT,KC_DOWN , KC_UP  , KC_RGHT, KC_QUOT,
        _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,
                                   _______, _______, _______,          _______, _______, _______
    ),


    /*
     * DOUBLE RAISE
     *
     *         ┌───┐                            ┌───┐
     *     ┌───┤   ├───┐                    ┌───┤   ├───┐
     * ┌───┤   ├───┤   ├───┐            ┌───┤   ├───┤   ├───┐
     * │   ├───┤   ├───┤   │            │   ├───┤   ├───┤B*T│
     * ├───┤   ├───┤   ├───┤            ├───┤   ├───┤   ├───┤
     * │   ├───┤   ├───┤   │            │   ├───┤   ├───┤   │
     * ├───┤   ├───┤   ├───┤            ├───┤   ├───┤   ├───┤
     * │   ├───┘   └───┤   │            │   ├───┘   └───┤   │
     * └───┘           └───┘            └───┘           └───┘
     *             ┌───┐                    ┌───┐
     *             │   ├───┐            ┌───┤   │
     *             └───┤   ├───┐    ┌───┤   ├───┘
     *                 └───┤   │    │   ├───┘
     *                     │   │    │   │
     *                     │   │    │   │
     *                     └───┘    └───┘
     *
     */

    [_DOUBLE_RAISE] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,                            _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,
                                   _______, _______, _______,          _______, _______, _______
    ),


    /*
     * ADJUST
     *
     *         ┌───┐                            ┌───┐
     *     ┌───┤   ├───┐                    ┌───┤   ├───┐
     * ┌───┤   ├───┤   ├───┐            ┌───┤   ├───┤   ├───┐
     * │   ├───┤   ├───┤   │            │   ├───┤MU ├───┤   │
     * ├───┤   ├───┤   ├───┤            ├───┤VD ├───┤VU ├───┤
     * │   ├───┤   ├───┤   │            │   ├───┤PLY├───┤   │
     * ├───┤   ├───┤   ├───┤            ├───┤PRV├───┤NXT├───┤
     * │   ├───┘   └───┤   │            │   ├───┘   └───┤   │
     * └───┘           └───┘            └───┘           └───┘
     *             ┌───┐                    ┌───┐
     *             │   ├───┐            ┌───┤   │
     *             └───┤   ├───┐    ┌───┤   ├───┘
     *                 └───┤   │    │   ├───┘
     *                     │   │    │   │
     *                     │   │    │   │
     *                     └───┘    └───┘
     *
     */
    [_ADJUST] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                            _______, KC_VOLD, KC_MUTE, KC_VOLU, _______,
        _______, _______, _______, _______, _______,                            _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,
                                   _______, _______, _______,          _______, _______, _______
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

int cur_dance(tap_dance_state_t *state) {
  if (state->count == 1) {
    // If count = 1, and it has been interrupted - it doesn't matter if it is
    // pressed or not: Send SINGLE_TAP
    if (state->interrupted) {
      //     if (!state->pressed) return SINGLE_TAP;
      // need "permissive hold" here.
      //     else return SINsGLE_HOLD;
      // If the interrupting key is released before the tap-dance key, then it
      // is a single HOLD However, if the tap-dance key is released first, then
      // it is a single TAP But how to get access to the state of the
      // interrupting key????
      return SINGLE_TAP;
    } else {
      if (!state->pressed)
        return SINGLE_TAP;
      else
        return SINGLE_HOLD;
    }
  }
  // If count = 2, and it has been interrupted - assume that user is trying to
  // type the letter associated with single tap.
  else if (state->count == 2) {
    if (state->interrupted)
      return DOUBLE_SINGLE_TAP;
    else if (state->pressed)
      return DOUBLE_HOLD;
    else
      return DOUBLE_TAP;
  } else if ((state->count == 2) && ((state->interrupted) || (!state->pressed)))
    return TRIPLE_TAP;
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed)))
    return TRIPLE_TAP;
  else if (state->count == 3)
    return TRIPLE_HOLD;
  else
    return UNKNOWN;
}

static xtap tap_lower_state = {.is_press_action = true, .state = 0};

void tap_lower_finished(tap_dance_state_t *state, void *user_data) {
  tap_lower_state.state = cur_dance(state);
  // single tap hold to switch lower, double hold to switch double LOWER
  switch (tap_lower_state.state) {
  case SINGLE_TAP:
    layer_on(_LOWER);
    break;
  case SINGLE_HOLD:
    layer_on(_LOWER);
    break;
  case DOUBLE_HOLD:
    layer_on(_DOUBLE_LOWER);
    break;
  }
}

void tap_lower_reset(tap_dance_state_t *state, void *user_data) {
  switch (tap_lower_state.state) {
  case SINGLE_TAP:
    layer_off(_LOWER);
    break;
  case SINGLE_HOLD:
    layer_off(_LOWER);
    break;
  case DOUBLE_HOLD:
    layer_off(_DOUBLE_LOWER);
    break;
  }
  tap_lower_state.state = 0;
}

static xtap tap_raise_state = {.is_press_action = true, .state = 0};

void tap_raise_finished(tap_dance_state_t *state, void *user_data) {
  tap_raise_state.state = cur_dance(state);
  // single tap hold to switch raise, double hold to switch double raise
  switch (tap_raise_state.state) {
  case SINGLE_TAP:
    layer_on(_RAISE);
    break;
  case SINGLE_HOLD:
    layer_on(_RAISE);
    break;
  case DOUBLE_HOLD:
    layer_on(_DOUBLE_RAISE);
    break;
  }
}

void tap_raise_reset(tap_dance_state_t *state, void *user_data) {
  switch (tap_raise_state.state) {
  case SINGLE_TAP:
    layer_off(_RAISE);
    break;
  case SINGLE_HOLD:
    layer_off(_RAISE);
    break;
  case DOUBLE_HOLD:
    layer_off(_DOUBLE_RAISE);
    break;
  }
  tap_raise_state.state = 0;
}

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LOWER] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_lower_finished, tap_lower_reset),
    [TD_RAISE] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_raise_finished, tap_raise_reset),
};

uint16_t achordion_timeout(uint16_t tap_hold_keycode) { return 600; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) {
    return false;
  }
  // Your macros ...

  return true;
}

void matrix_scan_user(void) { achordion_task(); }

/* #define Z_LSFT LSFT_T(KC_Z) */
/* #define SLSH_RSFT RSFT_T(KC_SLSH) */
/* #define EQL_LSFT LSFT_T(KC_EQL) */
/* #define RBRC_RSFT RSFT_T(KC_RBRC) */
/**/
/* #define SCLN_CTL RCTL_T(KC_SCLN) */
/* #define A_CTL LCTL_T(KC_A) */
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case Z_LSFT:
  case SLSH_RSFT:
  case EQL_LSFT:
  case RBRC_RSFT:
  case SCLN_CTL:
  case A_CTL:
  case J_GUI:
  case G_GUI:
    return QUICK_TAP_TERM - 90;
  default:
    return QUICK_TAP_TERM; // Enable key repeating.
  }
}
