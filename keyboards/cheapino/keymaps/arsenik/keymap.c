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

enum custom_keycodes {
    ASCII_SPACE = SAFE_RANGE,
};

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
        XX, XX, XX, XX, XX, XX,      KC_CAPS, KC_APP, XX, XX, XX, XX,
        XX, XX, XX, XX, XX, XX,      TG(_NUM_EDIT), XX, XX, XX, TG(_MOUSE), XX,
        XX, XX, XX, XX, XX, XX,      XX, XX, XX, XX, XX, XX,
                    XX, XX, XX,      XX, XX, XX
    ),

};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x5_3(
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', '*', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
    'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R',
                   '*', '*', '*', '*', 'R', 'R'
);

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
    }
    return true;
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
