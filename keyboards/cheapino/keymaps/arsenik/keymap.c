#include QMK_KEYBOARD_H
#include "arsenik.h"

enum arsenik_layers {
    _base,
    _lafayette,
    _num_row,
    _vim_nav,
    _num_nav,
    _fun_pad,
    _mouse_pad,
};

#define VOLD_MUTE LT(_base, KC_VOLD)

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

    [_base] = ARSENIK_LAYOUT(
        KC_CAPS, KC_1, KC_2,  KC_3,  KC_4,  KC_5,      KC_6, KC_7,  KC_8,    KC_9,   KC_0,    KC_DEL,
        KC_TAB,  KC_Q, KC_W,  KC_E,  KC_R,  KC_T,      KC_Y, KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_ESC,  KC_AA, KC_SS, KC_DD, KC_FF, KC_G,      KC_H, KC_JJ, KC_KK,   KC_LL,  KC_SSCLN, KC_ENTER,
        KC_LSFT, KC_Z, KC_X,  KC_C,  KC_V,  KC_B,      KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
         AS_TL_TUCK,   AS_TL_HOME,   AS_TL_REACH,      AS_TR_REACH,   AS_TR_HOME,   AS_TR_TUCK
    ),

    [_lafayette] = ARSENIK_LAYOUT(
        __, AG(KC_1), AG(KC_2), AG(KC_3), AG(KC_4), AG(KC_5),      AG(KC_6), AG(KC_7), AG(KC_8), AG(KC_9), AG(KC_0), __,
        __, AS(CIRC), AS(LT),   AS(GT),   AS(DLR),  AS(PERC),      AS(AT),   AS(AMPR), AS(ASTR), AS(QUOT), AS(GRV),  __,
        __, AS(LCBR), AS(LPRN), AS(RPRN), AS(RCBR), AS(EQL),       AS(BSLS), AS(PLUS), AS(MINS), AS(SLSH), AS(DQUO), __,
        __, AS(TILD), AS(LBRC), AS(RBRC), AS(UNDS), AS(HASH),      AS(PIPE), AS(EXLM), AS(SCLN), AS(COLN), AS(QUES), __,
                                MO(_num_row),   KC_SPC,   __,      __,   KC_BSPC,   MO(_num_row)
    ),

    [_num_row] = ARSENIK_LAYOUT(
        __, __,    __,    __,    __,    __,         __,    __,       __,       __,      __,       __,
        __, AS_S1, AS_S2, AS_S3, AS_S4, AS_S5,      AS_S6, AS_S7,    AS_S8,    AS_S9,   AS_S0,    __,
        __, AS(1), AS(2), AS(3), AS(4), AS(5),      AS(6), AS(7),    AS(8),    AS(9),   AS(0),    __,
        __, UC(0x201E), UC(0x201C), UC(0x201D), UC(0x00A2), UC(0x2030),      XX, AS(MINS), AS(COMM), AS(DOT), AS(SLSH), __,
                                     LAFAYETTE,   KC_SPC,   __,      __,   KC_BSPC,   LAFAYETTE
    ),

    [_vim_nav] = ARSENIK_LAYOUT(
        __, G(KC_1),      G(KC_2),  G(KC_3),   G(KC_4),  G(KC_5), G(KC_6),  G(KC_7),  G(KC_8), G(KC_9), G(KC_0),      __,
        __, MO(_num_nav), C(AS(T)), KC_WBAK,   KC_WFWD,  XX,      KC_HOME,  KC_PGDN,  KC_PGUP, KC_END,  G(AS(P)),     __,
        __, C(AS(A)),     C(AS(S)), S(KC_TAB), KC_TAB,   XX,      KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, MO(_fun_pad), __,
        __, C(AS(Z)),     C(AS(X)), C(AS(C)),  C(AS(V)), XX,      MS_WHLL,  MS_WHLD,  MS_WHLU, MS_WHLR, XX,           __,
                                         __,   __,   __,      __,   KC_DEL,   KC_ESC
    ),

    [_num_nav] = ARSENIK_LAYOUT(
        __, G(KC_1),  G(KC_2),  G(KC_3),  G(KC_4),  G(KC_5),        G(KC_6),  G(KC_7),  G(KC_8), G(KC_9), G(KC_0),  __,
        __, KC_TAB,   KC_HOME,  KC_UP,    KC_END,   KC_PGUP,        AS(SLSH), AS(7),    AS(8),   AS(9),   G(AS(P)), __,
        __, C(AS(A)), KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,        AS(MINS), AS(4),    AS(5),   AS(6),   AS(0),    __,
        __, C(AS(Z)), C(AS(X)), C(AS(C)), C(AS(V)), S(KC_TAB),      AS(COMM), AS(1),    AS(2),   AS(3),   AS(DOT),  __,
                                           __,   __,   __,      __,   KC_DEL,   KC_ESC
    ),

    [_fun_pad] = ARSENIK_LAYOUT(
        __, __,    __,     __,     __,     __,      __,      __,      __,      __,        __,      __,
        __, KC_F1, KC_F2,  KC_F3,  KC_F4,  XX,      KC_PSCR, KC_BRID, KC_BRIU, VOLD_MUTE, KC_VOLU, __,
        __, KC_F5, KC_F6,  KC_F7,  KC_F8,  XX,      XX,      KC_LCTL, KC_LSFT, KC_LALT,   KC_LGUI, __,
        __, KC_F9, KC_F10, KC_F11, KC_F12, XX,      XX,      KC_MPRV, KC_MPLY, KC_MNXT,   XX,      __,
                         LAFAYETTE,   KC_SPC,   __,      __,   KC_BSPC,   LAFAYETTE
    ),

    [_mouse_pad] = ARSENIK_LAYOUT(
        __, __, __, __, __, __,      __,      __,      __,      __,      __, __,
        __, XX, XX, XX, XX, XX,      XX,      MS_BTN1, MS_BTN3, MS_BTN2, XX, __,
        __, XX, XX, XX, XX, XX,      MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XX, __,
        __, XX, XX, XX, XX, XX,      MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XX, __,
             KC_DEL,   __,   __,      __,   __,   KC_ESC
    ),

};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x5_3(
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', '*', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
                   'L', 'L', 'L', 'R', 'R', 'R'
);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == VOLD_MUTE && !record->tap.count && record->event.pressed) {
        tap_code16(KC_MUTE);
        return false;
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
