// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "keymap_ergol.h"

#define XX KC_NO
#define __ KC_TRNS
#define AS(stripped_keycode) EL_##stripped_keycode

#define KC_AA LGUI_T(KC_A)
#define KC_SS LALT_T(KC_S)
#define KC_DD LSFT_T(KC_D)
#define KC_FF LCTL_T(KC_F)
#define KC_JJ RCTL_T(KC_J)
#define KC_KK RSFT_T(KC_K)
#define KC_LL RALT_T(KC_L)
#define KC_SSCLN RGUI_T(KC_SCLN)

#define AS_TL_TUCK LT(_NAV, KC_ESC)
