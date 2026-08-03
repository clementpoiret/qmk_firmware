// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "arsenik.h"
#include "framework.h"

enum arsenik_layers {
    _BASE,
    _NAV,
    _NUM_EDIT,
    _MOUSE,
    _FW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID, KC_BRIU, FW_SCRN, FW_AIRP, KC_PSCR, KC_MSEL, KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        AS_TL_TUCK, KC_AA,   KC_SS,   KC_DD,   KC_FF,   KC_G,    KC_H,    KC_JJ,   KC_KK,   KC_LL,   KC_SSCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, MO(_FW), LT(_MOUSE, KC_TAB), AS_TL_TUCK, KC_SPC,                KC_RALT, LT(_NUM_EDIT, KC_ENT), KC_LEFT, KC_UP, KC_DOWN, KC_RGHT
    ),

    [_NAV] = LAYOUT(
        __, __,            __,            __,         __,         __,       __,      __,           __,         __,       __,      __, __, __,
        __, __,            __,            __,         __,         __,       __,      __,           __,         __,       __,      __, __, __,
        __, C(KC_LEFT),    C(KC_RGHT),    C(KC_BSPC), C(KC_DEL),  QK_REP,   KC_WBAK, KC_HOME,      KC_PGDN,    KC_PGUP,  KC_END,  __, __, __,
        __, C(AS(A)),      C(AS(Z)),      C(S(AS(Z))), C(AS(C)),  C(AS(V)), KC_WFWD, KC_LEFT,      KC_DOWN,    KC_UP,    KC_RGHT, __,     __,
        __,                C(S(KC_LEFT)), C(S(KC_RGHT)), S(KC_HOME), S(KC_END), C(AS(X)), XX, C(S(KC_TAB)), C(KC_TAB), XX, XX,              __,
        __, XX, KC_TAB, KC_ESC, KC_SPC, KC_RALT, KC_ENT, __, __, __, __
    ),

    [_NUM_EDIT] = LAYOUT(
        __, __,       __,         __,         __,         __,         __,       __,   __,   __,   __,       __, __, __,
        __, __,       __,         __,         __,         __,         __,       __,   __,   __,   __,       __, __, __,
        __, AS(EQL),  KC_HOME,    KC_UP,      KC_END,     KC_PGUP,    AS(SLSH), KC_7, KC_8, KC_9, AS(ASTR), __, __, __,
        __, AS(PLUS), KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,    AS(MINS), KC_4, KC_5, KC_6, KC_0,     __,     __,
        __,           AS(ODK),    C(KC_LEFT), C(KC_BSPC), C(KC_DEL), C(KC_RGHT), AS(COMM), KC_1, KC_2, KC_3, AS(DOT),    __,
        __, XX, KC_TAB, KC_BSPC, KC_ENT, XX, TG(_NUM_EDIT), __, __, __, __
    ),

    [_MOUSE] = LAYOUT(
        __, __,      __,      __,      __,      __, __,      __,      __,      __,      __,      __, __, __,
        __, __,      __,      __,      __,      __, __,      __,      __,      __,      __,      __, __, __,
        __, MS_ACL0, MS_ACL2, XX,      XX,      XX, MS_BTN4, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, __, __, __,
        __, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XX, MS_BTN5, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, __,     __,
        __,          MS_BTN1, MS_BTN2, MS_BTN3, XX, XX, XX, XX, XX, XX, XX,             __,
        __, XX, TG(_MOUSE), TO(_BASE), KC_SPC, KC_BSPC, KC_ESC, __, __, __, __
    ),

    [_FW] = LAYOUT(
        __, KC_F1, KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,       KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_INS,
        __, __,    __,     __,      __,      __,      __,      __,          __,      __,      __,      __,      __,         __,
        __, __,    RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_SPDU, RM_VALU,    RM_SPDD, KC_CAPS, KC_APP,  KC_PAUS, __,         __,
        __, __,    __,     RM_PREV, RM_HUED, RM_SATD, TG(_NUM_EDIT), RM_VALD, KC_SCRL, __,    TG(_MOUSE), __,               __,
        __,         __,    __,      BL_BRTG, __,      KC_BRK,  __,          __,      __,      __,      __,                  __,
        __, __, KC_TAB, KC_ESC, BL_STEP, KC_RALT, KC_ENT, KC_HOME, KC_PGUP, KC_PGDN, KC_END
    ),
};

// Only the four layer-tap positions and Space are exempt from the
// opposite-hands rule. The hand split follows conventional touch typing.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
    '*', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',      'R',
    'L',      'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R',      'R',
    'L', 'L', '*', '*', '*', 'R', '*', 'R', 'R', 'R', 'R'
);

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    if (IS_QK_MOD_TAP(keycode)) {
        return ARSENIK_HRM_TAPPING_TERM;
    }
    return ARSENIK_LAYER_TAPPING_TERM;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    if (IS_QK_MOD_TAP(keycode)) {
        return ARSENIK_HRM_QUICK_TAP_TERM;
    }
    return 0;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return IS_QK_MOD_TAP(keycode);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return keycode == AS_TL_TUCK || keycode == LT(_MOUSE, KC_TAB) || keycode == LT(_NUM_EDIT, KC_ENT);
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    (void)record;
    if (IS_QK_MOD_TAP(keycode) && is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}

#ifdef RGB_MATRIX_ENABLE
static void set_layer_key_color(uint8_t layer, uint8_t led_min, uint8_t led_max, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            const uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index == NO_LED || led_index < led_min || led_index >= led_max) {
                continue;
            }

            const uint16_t keycode = pgm_read_word(&keymaps[layer][row][col]);
            if (keycode != KC_TRNS && keycode != KC_NO) {
                rgb_matrix_set_color(led_index, red, green, blue);
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const uint8_t active_layer = get_highest_layer(layer_state);

    switch (active_layer) {
        case _NAV:
            set_layer_key_color(_NAV, led_min, led_max, RGB_BLUE);
            break;
        case _NUM_EDIT:
            set_layer_key_color(_NUM_EDIT, led_min, led_max, RGB_GREEN);
            break;
        case _MOUSE:
            set_layer_key_color(_MOUSE, led_min, led_max, RGB_MAGENTA);
            break;
        case _FW:
            set_layer_key_color(_FW, led_min, led_max, RGB_YELLOW);
            break;
    }

    return false;
}
#endif
