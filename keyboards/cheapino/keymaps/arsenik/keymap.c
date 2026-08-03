// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "arsenik.h"
#include "matrix_encoder.h"

#ifdef CONSOLE_ENABLE
#    include "debug.h"
#    include "print.h"
#endif

enum arsenik_layers {
    _BASE,
    _NAV,
    _NUM_EDIT,
    _FUNCTION,
    _MOUSE,
    _SYSTEM,
};

enum arsenik_rgb_layers {
    _RGB_NAV,
    _RGB_NUM_EDIT,
    _RGB_FUNCTION,
    _RGB_MOUSE,
    _RGB_SYSTEM,
};

enum custom_keycodes {
    ASCII_SPACE = SAFE_RANGE,
    CHEAPINO_DIAG,
};

#ifdef CONSOLE_ENABLE
#    define CK_DIAG CHEAPINO_DIAG
#else
#    define CK_DIAG KC_NO
#endif

const rgblight_segment_t PROGMEM nav_rgb_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM num_edit_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM function_rgb_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});
const rgblight_segment_t PROGMEM mouse_rgb_layer[]    = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_MAGENTA});
const rgblight_segment_t PROGMEM system_rgb_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});

const rgblight_segment_t *const PROGMEM arsenik_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    nav_rgb_layer,
    num_edit_rgb_layer,
    function_rgb_layer,
    mouse_rgb_layer,
    system_rgb_layer
);

// ARSENIK_LAYOUT keeps the source keymap in its original 4x6+3 shape and
// selects the physical 3x5+3 positions used by Cheapino.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = ARSENIK_LAYOUT(
        KC_CAPS, KC_1, KC_2,  KC_3,  KC_4,  KC_5,      KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_DEL,
        KC_TAB,  KC_Q, KC_W,  KC_E,  KC_R,  KC_T,      KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_ESC,  KC_AA, KC_SS, KC_DD, KC_FF, KC_G,      KC_H, KC_JJ, KC_KK,   KC_LL,  KC_SSCLN, KC_ENTER,
        KC_LSFT, KC_Z, KC_X,  KC_C,  KC_V,  KC_B,      KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
         AS_TL_TUCK,   AS_TL_HOME,   AS_TL_REACH,      AS_TR_REACH,   AS_TR_HOME,   AS_TR_TUCK
    ),

    [_NAV] = ARSENIK_LAYOUT(
        __, __,            __,            __,         __,         __,       __,      __,         __,         __,        __,      __,
        __, C(KC_LEFT),    C(KC_RGHT),    C(KC_BSPC), C(KC_DEL),  QK_REP,   KC_WBAK, KC_HOME,    KC_PGDN,    KC_PGUP,   KC_END,  __,
        __, C(AS(A)),      C(AS(Z)),      C(S(AS(Z))), C(AS(C)),  C(AS(V)), KC_WFWD, KC_LEFT,    KC_DOWN,    KC_UP,     KC_RGHT, __,
        __, C(S(KC_LEFT)), C(S(KC_RGHT)), S(KC_HOME), S(KC_END), C(AS(X)),  XX,      C(S(KC_TAB)), C(KC_TAB), XX,        XX,      __,
                                               __,   __,   __,      __,   KC_DEL,   KC_ESC
    ),

    [_NUM_EDIT] = ARSENIK_LAYOUT(
        __, __,          __,         __,         __,         __,           __,       __,   __,   __,   __,       __,
        __, AS(EQL),     KC_HOME,    KC_UP,      KC_END,     KC_PGUP,      AS(SLSH), KC_7, KC_8, KC_9, AS(ASTR), __,
        __, AS(PLUS),    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,      AS(MINS), KC_4, KC_5, KC_6, KC_0,     __,
        __, AS(ODK),     C(KC_LEFT), C(KC_BSPC), C(KC_DEL), C(KC_RGHT),   AS(COMM), KC_1, KC_2, KC_3, AS(DOT),  __,
                                      KC_TAB,   KC_BSPC,   KC_ENT,      TG(_NUM_EDIT),   XX,   XX
    ),

    [_FUNCTION] = ARSENIK_LAYOUT(
        __, __,    __,     __,     __,     __,      __,      __,      __,      __,        __,      __,
        __, KC_F1, KC_F2,  KC_F3,  KC_F4,  XX,      KC_PSCR, KC_BRID, KC_BRIU, KC_MUTE,   ASCII_SPACE, __,
        __, KC_F5, KC_F6,  KC_F7,  KC_F8,  XX,      KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI,   XX,      __,
        __, KC_F9, KC_F10, KC_F11, KC_F12, XX,      KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD,   KC_VOLU, __,
                         OSM(MOD_RALT),   KC_SPC,   XX,      OSM(MOD_LSFT),   KC_BSPC,   MO(_SYSTEM)
    ),

    [_MOUSE] = ARSENIK_LAYOUT(
        __, __, __, __, __, __,      __,      __,      __,      __,      __, __,
        __, MS_ACL0, MS_ACL2, XX, XX, XX,      MS_BTN4, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, __,
        __, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI, XX,      MS_BTN5, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, __,
        __, MS_BTN1, MS_BTN2, MS_BTN3, XX, XX,      XX, XX, XX, XX, XX, __,
             TO(_BASE),   KC_SPC,   TG(_MOUSE),      XX,   KC_BSPC,   KC_ESC
    ),

    [_SYSTEM] = ARSENIK_LAYOUT(
        XX, XX, XX, XX, XX, XX,      XX, XX, XX, XX, XX, XX,
        XX, QK_BOOT, CK_DIAG, XX, XX, XX,      XX, XX, XX, KC_CAPS, KC_APP, XX,
        XX, XX, XX, XX, XX, XX,      TG(_NUM_EDIT), XX, XX, XX, TG(_MOUSE), XX,
        XX, XX, XX, XX, XX, XX,      XX, XX, XX, XX, XX, XX,
                    XX, XX, XX,      XX, XX, XX
    ),

};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]     = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_NAV]      = {ENCODER_CCW_CW(C(S(KC_TAB)), C(KC_TAB))},
    [_NUM_EDIT] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FUNCTION] = {ENCODER_CCW_CW(C(AS(Z)), C(S(AS(Z))))},
    [_MOUSE]    = {ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
    [_SYSTEM]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};

// Only layer-tap thumbs are exempt from the opposite-hands rule.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x5_3(
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
                   '*', '*', '*', '*', 'R', 'R'
);

void keyboard_post_init_user(void) {
    rgblight_layers = arsenik_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_RGB_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_RGB_NUM_EDIT, layer_state_cmp(state, _NUM_EDIT));
    rgblight_set_layer_state(_RGB_FUNCTION, layer_state_cmp(state, _FUNCTION));
    rgblight_set_layer_state(_RGB_MOUSE, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(_RGB_SYSTEM, layer_state_cmp(state, _SYSTEM));
    return state;
}

static void tap_ascii_space(void) {
    const uint8_t suppressed_mods = MOD_MASK_SHIFT | MOD_BIT(KC_RALT);
    const uint8_t mods            = get_mods();
    const uint8_t weak_mods       = get_weak_mods();
    const uint8_t oneshot_mods    = get_oneshot_mods();
    const uint8_t locked_mods     = get_oneshot_locked_mods();

    del_mods(suppressed_mods);
    del_weak_mods(suppressed_mods);
    del_oneshot_mods(suppressed_mods);
    del_oneshot_locked_mods(suppressed_mods);
    send_keyboard_report();

    tap_code(KC_SPC);

    set_mods(mods);
    set_weak_mods(weak_mods);
    set_oneshot_mods(oneshot_mods);
    set_oneshot_locked_mods(locked_mods);
    send_keyboard_report();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ASCII_SPACE:
            if (record->event.pressed) {
                tap_ascii_space();
            }
            return false;
#ifdef CONSOLE_ENABLE
        case CHEAPINO_DIAG:
            if (record->event.pressed) {
                const bool enabled = !(debug_enable && debug_matrix);
                debug_enable       = enabled;
                debug_matrix       = enabled;
                dprintf("cheapino diagnostics: %s\n", enabled ? "on" : "off");
            }
            return false;
#endif
    }
    return true;
}

bool cheapino_encoder_button_update_user(bool pressed) {
    if (!pressed) {
        tap_code(KC_MUTE);
    }
    return false;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    if (IS_QK_MOD_TAP(keycode)) {
        return ARSENIK_HRM_TAPPING_TERM;
    }
    return ARSENIK_THUMB_TAPPING_TERM;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    if (IS_QK_MOD_TAP(keycode)) {
        return ARSENIK_HRM_QUICK_TAP_TERM;
    }
    if (keycode == LT(_FUNCTION, KC_SPC)) {
        return ARSENIK_SPACE_QUICK_TAP_TERM;
    }
    return 0;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return IS_QK_MOD_TAP(keycode) || keycode == LT(_FUNCTION, KC_SPC);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return keycode == LT(_NAV, KC_ESC) || keycode == LT(_MOUSE, KC_TAB) || keycode == LT(_NUM_EDIT, KC_ENT);
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    (void)record;
    if (IS_QK_MOD_TAP(keycode) && is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}
