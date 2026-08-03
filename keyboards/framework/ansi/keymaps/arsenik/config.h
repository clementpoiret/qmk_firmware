// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Match the Cheapino/Corne Arsenik timing contract while keeping the
// Framework-specific layer keys independent of recently typed characters.
#define ARSENIK_HRM_TAPPING_TERM 200
#define ARSENIK_LAYER_TAPPING_TERM 150
#define ARSENIK_HRM_QUICK_TAP_TERM 175

#define TAPPING_TERM ARSENIK_HRM_TAPPING_TERM
#define TAPPING_TERM_PER_KEY

#define QUICK_TAP_TERM 0
#define QUICK_TAP_TERM_PER_KEY

#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
