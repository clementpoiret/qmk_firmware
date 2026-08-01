#include QMK_KEYBOARD_H
#include "arsenik.h"

enum arsenik_layers {
    _BASE,
    _NAV,
    _NUM_EDIT,
    _FUNCTION,
    _MOUSE,
    _SYSTEM,
};

#define VOLD_MUTE LT(_BASE, KC_VOLD)

// The ARSENIK_LAYOUT macro allows us to declare a config for a 4x6+3 keyboard, then truncate it
// (or fill it with noops) depending on the size of your keyboard. Your keyboard may have extra
// definitions for this macro or none at all (preventing you from compiling the keymap). Check
// the `README.md` file for more information.
//
// A comprehensive list of QMK keycodes is available here: https://docs.qmk.fm/keycodes
// However, we used a many aliases to automatically adapt the keymap depending on the options you
// enabled in the `config.h` file (or just to have some syntaxic sugar). You can find all of them
// in the `arsenik.h` file. Feel free to remove those aliases and replace them with their actual
// value if you need something Arsenik doesn’t provide.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = ARSENIK_LAYOUT(
        KC_CAPS, KC_1, KC_2,  KC_3,  KC_4,  KC_5,      KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_DEL,
        KC_TAB,  KC_Q, KC_W,  KC_E,  KC_R,  KC_T,      KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_ESC,  KC_AA, KC_SS, KC_DD, KC_FF, KC_G,      KC_H, KC_JJ, KC_KK,   KC_LL,  KC_SSCLN, KC_ENTER,
        KC_LSFT, KC_Z, KC_X,  KC_C,  KC_V,  KC_B,      KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
         AS_TL_TUCK,   AS_TL_HOME,   AS_TL_REACH,      AS_TR_REACH,   AS_TR_HOME,   AS_TR_TUCK
    ),

    [_NAV] = ARSENIK_LAYOUT(
        __, G(AS(1)),      G(AS(2)),  G(AS(3)),   G(AS(4)),  G(AS(5)), G(AS(6)),  G(AS(7)),  G(AS(8)), G(AS(9)), G(AS(0)),      __,
        __, MO(_NUM_EDIT), C(AS(T)), KC_WBAK,   KC_WFWD,  XX,      KC_HOME,  KC_PGDN,  KC_PGUP, KC_END,  G(AS(P)),       __,
        __, C(AS(A)),      C(AS(S)), S(KC_TAB), KC_TAB,   XX,      KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, MO(_FUNCTION), __,
        __, C(AS(Z)),     C(AS(X)), C(AS(C)),  C(AS(V)), XX,      MS_WHLL,  MS_WHLD,  MS_WHLU, MS_WHLR, XX,           __,
                                         __,   __,   __,      __,   KC_DEL,   KC_ESC
    ),

    [_NUM_EDIT] = ARSENIK_LAYOUT(
        __, __,          __,         __,         __,         __,           __,       __,   __,   __,   __,       __,
        __, AS(EQL),     KC_HOME,    KC_UP,      KC_END,     KC_PGUP,      AS(SLSH), KC_7, KC_8, KC_9, AS(ASTR), __,
        __, AS(PLUS),    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,      AS(MINS), KC_4, KC_5, KC_6, KC_0,     __,
        __, AS(ODK),     C(KC_LEFT), C(KC_BSPC), C(KC_DEL), C(KC_RGHT),   AS(COMM), KC_1, KC_2, KC_3, AS(DOT),  __,
                                      KC_TAB,   KC_BSPC,   KC_ENT,      __,   XX,   XX
    ),

    [_FUNCTION] = ARSENIK_LAYOUT(
        __, __,    __,     __,     __,     __,      __,      __,      __,      __,        __,      __,
        __, KC_F1, KC_F2,  KC_F3,  KC_F4,  XX,      KC_PSCR, KC_BRID, KC_BRIU, VOLD_MUTE, KC_VOLU, __,
        __, KC_F5, KC_F6,  KC_F7,  KC_F8,  XX,      XX,      KC_LCTL, KC_LSFT, KC_LALT,   KC_LGUI, __,
        __, KC_F9, KC_F10, KC_F11, KC_F12, XX,      XX,      KC_MPRV, KC_MPLY, KC_MNXT,   XX,      __,
                         OSM(MOD_RALT),   KC_SPC,   __,      __,   KC_BSPC,   MO(_SYSTEM)
    ),

    [_MOUSE] = ARSENIK_LAYOUT(
        __, __, __, __, __, __,      __,      __,      __,      __,      __, __,
        __, XX, XX, XX, XX, XX,      XX,      MS_BTN1, MS_BTN3, MS_BTN2, XX, __,
        __, XX, XX, XX, XX, XX,      MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XX, __,
        __, XX, XX, XX, XX, XX,      MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XX, __,
             KC_DEL,   __,   __,      __,   __,   KC_ESC
    ),

    [_SYSTEM] = ARSENIK_LAYOUT(
        XX, XX, XX, XX, XX, XX,      XX, XX, XX, XX, XX, XX,
        XX, XX, XX, XX, XX, XX,      XX, XX, XX, XX, XX, XX,
        XX, XX, XX, XX, XX, XX,      XX, XX, XX, XX, XX, XX,
        XX, XX, XX, XX, XX, XX,      XX, XX, XX, XX, XX, XX,
                    XX, XX, XX,      XX, XX, XX
    ),

};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x5_3(
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', '*', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
                   'L', 'L', 'L', 'R', 'R', 'R'
);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VOLD_MUTE:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_MUTE);
                return false;
            }
            break;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    if (IS_QK_MOD_TAP(keycode) || keycode == VOLD_MUTE) {
        return ARSENIK_HRM_TAPPING_TERM;
    }
    return ARSENIK_THUMB_TAPPING_TERM;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return IS_QK_MOD_TAP(keycode) ? ARSENIK_QUICK_TAP_TERM : 0;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    (void)record;
    return keycode != VOLD_MUTE;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    (void)keycode;
    (void)record;
    (void)prev_keycode;
    return FLOW_TAP_TERM;
}
