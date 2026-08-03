// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// This keymap intentionally fixes the Arsenik variant to eight home-row mods,
// six Selenium-style thumbs, and a host-side Ergo-L layout.
#define ARSENIK_HRM_TAPPING_TERM 200
#define ARSENIK_THUMB_TAPPING_TERM 150
#define ARSENIK_HRM_QUICK_TAP_TERM 175
#define ARSENIK_SPACE_QUICK_TAP_TERM 175

#define ONESHOT_TIMEOUT 1000

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL

#define TAPPING_TERM ARSENIK_HRM_TAPPING_TERM
#define TAPPING_TERM_PER_KEY

#define QUICK_TAP_TERM 0
#define QUICK_TAP_TERM_PER_KEY

#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
