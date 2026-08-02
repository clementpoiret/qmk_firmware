// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix_encoder.h"

#include <stdint.h>

#include "encoder.h"
#include "quantum.h"

#ifdef CONSOLE_ENABLE
#    include "debug.h"
#    include "print.h"
#endif

#define CHEAPINO_ENCODER_ROW 3
#define CHEAPINO_ENCODER_A_COL 2
#define CHEAPINO_ENCODER_B_COL 4
#define CHEAPINO_ENCODER_BUTTON_COL 0

#define CHEAPINO_ENCODER_A_BIT ((matrix_row_t)1U << CHEAPINO_ENCODER_A_COL)
#define CHEAPINO_ENCODER_B_BIT ((matrix_row_t)1U << CHEAPINO_ENCODER_B_COL)
#define CHEAPINO_ENCODER_MASK (CHEAPINO_ENCODER_A_BIT | CHEAPINO_ENCODER_B_BIT)

enum encoder_transition {
    TRANSITION_COUNTER_CLOCKWISE = -1,
    TRANSITION_NONE              = 0,
    TRANSITION_CLOCKWISE         = 1,
    TRANSITION_INVALID           = 2,
};

// States use A as bit 0 and B as bit 1. The clockwise sequence observed on
// Cheapino v2 is 00 -> 10 -> 11 -> 01 -> 00.
static const int8_t encoder_transition_table[16] = {
    TRANSITION_NONE, TRANSITION_COUNTER_CLOCKWISE, TRANSITION_CLOCKWISE, TRANSITION_INVALID,
    TRANSITION_CLOCKWISE, TRANSITION_NONE, TRANSITION_INVALID, TRANSITION_COUNTER_CLOCKWISE,
    TRANSITION_COUNTER_CLOCKWISE, TRANSITION_INVALID, TRANSITION_NONE, TRANSITION_CLOCKWISE,
    TRANSITION_INVALID, TRANSITION_CLOCKWISE, TRANSITION_COUNTER_CLOCKWISE, TRANSITION_NONE,
};

static uint8_t encoder_raw_state;
static uint8_t encoder_previous_state;
static int8_t  encoder_transition_count;
static bool    encoder_state_initialized;
static bool    encoder_button_pressed;

void cheapino_encoder_capture(matrix_row_t current_matrix[]) {
    const matrix_row_t encoder_row = current_matrix[CHEAPINO_ENCODER_ROW];

    encoder_raw_state = 0;
    if (encoder_row & CHEAPINO_ENCODER_A_BIT) {
        encoder_raw_state |= 1U;
    }
    if (encoder_row & CHEAPINO_ENCODER_B_BIT) {
        encoder_raw_state |= 2U;
    }

    // Quadrature contacts are not keys. Keep the push button and every other
    // bit in this row available to the normal matrix debounce pipeline.
    current_matrix[CHEAPINO_ENCODER_ROW] &= ~CHEAPINO_ENCODER_MASK;
}

void encoder_driver_init(void) {
    encoder_raw_state         = 0;
    encoder_previous_state    = 0;
    encoder_transition_count  = 0;
    encoder_state_initialized = false;
    encoder_button_pressed    = false;
}

void encoder_driver_task(void) {
    const uint8_t current_state = encoder_raw_state;

    if (!encoder_state_initialized) {
        encoder_previous_state    = current_state;
        encoder_state_initialized = true;
        return;
    }

    if (current_state == encoder_previous_state) {
        return;
    }

    const uint8_t transition_index = (encoder_previous_state << 2) | current_state;
    const int8_t  transition       = encoder_transition_table[transition_index];

#ifdef CONSOLE_ENABLE
    if (debug_enable && debug_matrix) {
        dprintf("cheapino encoder: %u -> %u", encoder_previous_state, current_state);
    }
#endif

    encoder_previous_state = current_state;

    if (transition == TRANSITION_INVALID) {
        encoder_transition_count = 0;
#ifdef CONSOLE_ENABLE
        if (debug_enable && debug_matrix) {
            dprintf(" invalid, reset\n");
        }
#endif
        return;
    }

    encoder_transition_count += transition;

#ifdef CONSOLE_ENABLE
    if (debug_enable && debug_matrix) {
        dprintf(" count=%d\n", encoder_transition_count);
    }
#endif

    if (current_state != 0) {
        return;
    }

    if (encoder_transition_count >= 4) {
        encoder_queue_event(0, true);
    } else if (encoder_transition_count <= -4) {
        encoder_queue_event(0, false);
    }

    // A detent is the synchronization point. Do not carry a partial or stale
    // transition into the next physical movement.
    encoder_transition_count = 0;
}

__attribute__((weak)) bool cheapino_encoder_button_update_user(bool pressed) {
    return true;
}

bool cheapino_encoder_button_update_kb(bool pressed) {
    if (!cheapino_encoder_button_update_user(pressed)) {
        return false;
    }

    // Preserve the historical default for keymaps without a user callback.
    if (!pressed) {
        tap_code(KC_MUTE);
    }
    return true;
}

void cheapino_encoder_button_task(void) {
    const bool pressed = matrix_is_on(CHEAPINO_ENCODER_ROW, CHEAPINO_ENCODER_BUTTON_COL);
    if (pressed == encoder_button_pressed) {
        return;
    }

    encoder_button_pressed = pressed;
#ifdef CONSOLE_ENABLE
    if (debug_enable && debug_matrix) {
        dprintf("cheapino encoder button: %s\n", pressed ? "pressed" : "released");
    }
#endif
    cheapino_encoder_button_update_kb(pressed);
}
