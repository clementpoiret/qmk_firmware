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
#define AS_TL_HOME LT(_FUNCTION, KC_SPC)
#define AS_TL_REACH LT(_MOUSE, KC_TAB)
#define AS_TR_REACH LT(_NUM_EDIT, KC_ENT)
#define AS_TR_HOME KC_BSPC
#define AS_TR_TUCK KC_RALT

#define ARSENIK_LAYOUT(                                                                                               \
    k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,                                                     \
    k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c,                                                     \
    k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,                                                     \
    k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c,                                                     \
    k51, k52, k53, k54, k55, k56)                                                                                   \
    LAYOUT_split_3x5_3(                                                                                              \
        k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,                                                          \
        k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,                                                          \
        k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b,                                                          \
        k51, k52, k53, k54, k55, k56)
