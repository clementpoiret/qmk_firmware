// Copyright 2023 Thomas Haukland (@tompi)
// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#include "matrix_encoder.h"

// State for the non-blocking startup RGB sweep.
static uint8_t startup_hue_countdown = 50;
static uint8_t saved_hue;
static uint8_t saved_saturation;
static uint8_t saved_value;

static uint32_t flash_led(uint32_t next_trigger_time, void *cb_arg) {
    (void)next_trigger_time;
    (void)cb_arg;

    rgblight_sethsv_noeeprom(startup_hue_countdown * 5, 230, 70);
    startup_hue_countdown--;
    if (startup_hue_countdown == 0) {
        rgblight_sethsv_noeeprom(saved_hue, saved_saturation, saved_value);
        return 0;
    }
    return 50;
}

void keyboard_post_init_kb(void) {
    saved_hue        = rgblight_get_hue();
    saved_saturation = rgblight_get_sat();
    saved_value      = rgblight_get_val();

    defer_exec(50, flash_led, NULL);
    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
    cheapino_encoder_button_task();
    matrix_scan_user();
}
