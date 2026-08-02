//  ───────────────────< Basic QMK options for Arsenik >───────────────────

#define ARSENIK_HRM_TAPPING_TERM 200
#define ARSENIK_THUMB_TAPPING_TERM 150
#define ARSENIK_HRM_QUICK_TAP_TERM 175
#define ARSENIK_SPACE_QUICK_TAP_TERM 175
#define ONESHOT_TIMEOUT 1000

#undef TAPPING_TERM
#define TAPPING_TERM ARSENIK_HRM_TAPPING_TERM
#define TAPPING_TERM_PER_KEY

#define QUICK_TAP_TERM 0
#define QUICK_TAP_TERM_PER_KEY

#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define ARSENIK_LAYOUT_split_3x5_3
/* NOTE: This line gets automatically filled in by the install script, but the
 * underlying layout may not yet exist, and keyboard specific layout may have
 * other variants you might want to check out.
 */


//  ────────────────────< Main Arsenik configuration >─────────────────

// Below are a bunch of options to quickly customize the Arsenik keymap. You
// can pick and choose them by (un)commenting the different `#define`
// declarations.

#define ARSENIK_ENABLE_HRM
/* When active, adds a Meta, Ctrl and Alt home-row-mod on respectively s/l,
 * d/k or f/j on a Qwerty keyboard. Those home-row-mods stay on those exact
 * keys regardless of the layout being used, meaning they would be on r/i, s/e
 * and t/n on a Colemak keyboard.
 */

// #define ARSENIK_MAC_MODIFIERS
/* Swaps around home-row-mods from Meta, Ctrl, Alt to Alt, Meta, Ctrl, as it
 * may make more sense on a Mac, like to keep common shortcuts accessible with
 * the Ergo‑L layout, for instance
 *
 * (Requires `ARSENIK_ENABLE_HRM`)
 */

// #define ARSENIK_DISABLE_THUMB_TAP_HOLDS
/* When active, uses an extra simple config without any tap-holds on the thumb
 * keys. It may be a *lot* simpler to use, but requieres a keyboard with at
 * least 6 thumb keys (so 3 per thumb) instead of 3 thumb keys total and is
 * overall a lot less efficient (especially when combining modifiers).
 *
 * Base thumb config: LSFT_T(KC_ËSC)  LT(_NUM_EDIT, KC_SPC)  RALT_T(KC_ENT)
 * When it’s active: KC_ALT  KC_CTL  KC_GUI     MO(_NUM_EDIT)  KC_SPC  KC_RALT
 *
 * (Prevents using `ARSENIK_ENABLE_SELENIUM_VARIANT`)
 */

#define ARSENIK_ENABLE_SELENIUM_VARIANT
/* Most ergonomic keyboards have at least 4 comfortable thumb keys keys (so 2
 * per thumb). Selenium is a variant of Arsenik made to fit on 34 keys keyboard
 * to take advantage of the extra thumb key. It does it by splitting the numbers
 * and navigation layers to 2 distict layers, and adds an escape key.
 *
 * Base thumb config: LSFT_T(KC_ËSC)  LT(_NUM_EDIT, KC_SPC)  RALT_T(KC_ENT)
 * Selenium: LT(_NAV, KC_ESC) LT(_FUNCTION, KC_SPC) LT(_MOUSE, KC_TAB)
 *           LT(_NUM_EDIT, KC_ENT) KC_BSPC KC_RALT
 */

// #define SELENIUM_LEFT_HAND_SPACE
/* Swaps around the backspace and space keycodes, for people who prefer using
 * their left thunb for the space bar.
 *
 * (Requires `ARSENIK_ENABLE_SELENIUM_VARIANT`)
 */

// #define SELENIUM_RESTORE_SPACE
/* Having Space accessible to only one thumb may create some problems, especially
 * when trying to type Shift + Space or AltGr + Space (depending if your space
 * key is on your left or right hand). When active, backspace gets
 * temporarily replaced by space when the original space key is held.
 *
 * (Requires `ARSENIK_ENABLE_SELENIUM_VARIANT`)
 */


// Lists of layouts supported by Arsenik. Some parts of the config are dependent
// on keyboard layout used on your computer. If they don’t match up some
// characters may not be correctly placed or missing entirely. If multiple
// options are toggled at the same time, the first one is chosen.
// #define ARSENIK_HOST_LAYOUT_QWERTY
// #define ARSENIK_HOST_LAYOUT_AZERTY
#define ARSENIK_HOST_LAYOUT_ERGOL
// #define ARSENIK_HOST_LAYOUT_BEPO
// #define ARSENIK_HOST_LAYOUT_DVORAK
// #define ARSENIK_HOST_LAYOUT_COLEMAK
// #define ARSENIK_HOST_LAYOUT_WORKMAN
