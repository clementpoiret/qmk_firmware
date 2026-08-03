// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "framework.h"
#include "os_detection.h"

#ifdef RGB_MATRIX_ENABLE
#    include "is31fl3743a.h"

#    define IS31FL3743A_REG_TEST 0xE0
#    define IS31FL3743A_REG_CUSTOM_PWM 0xE2
#    define IS31FL3743A_CUSTOM_PWM_32KHZ 0xE0

static void set_rgb_pwm_frequency(void) {
    for (uint8_t index = 0; index < IS31FL3743A_DRIVER_COUNT; index++) {
        is31fl3743a_select_page(index, IS31FL3743A_COMMAND_FUNCTION);
        is31fl3743a_write_register(index, IS31FL3743A_REG_TEST, 0x01);
        is31fl3743a_write_register(index, IS31FL3743A_REG_CUSTOM_PWM, IS31FL3743A_CUSTOM_PWM_32KHZ);
        is31fl3743a_write_register(index, IS31FL3743A_REG_TEST, 0x00);
    }
}
#endif

bool is_suspended = false;

void keyboard_post_init_kb(void) {
#ifdef RGB_MATRIX_ENABLE
    // Raise the LED PWM frequency above the audible range, matching the
    // released Framework firmware.
    set_rgb_pwm_frequency();
#endif

    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;

    keyboard_post_init_user();
}

/**
 * Hook into early keyboard initialization
 */
void keyboard_pre_init_kb(void) {
    // Mark boot as done.
    // Before this, when holding down both alt keys QSPI_SS is pulled low to put
    // the RP2040 in bootloader mode during reset.
    gpio_set_pin_output(BOOT_DONE_GPIO);
    gpio_write_pin_low(BOOT_DONE_GPIO);

    // Keep the analog matrix multiplexer enabled while the keyboard is active.
    gpio_set_pin_output(MUX_ENABLE_GPIO);
    gpio_write_pin_high(MUX_ENABLE_GPIO);

    gpio_set_pin_output(IS31FL3743A_ENABLE_GPIO);
#if defined(RGB_MATRIX_ENABLE)
    gpio_write_pin_high(IS31FL3743A_ENABLE_GPIO);
#else
    gpio_write_pin_low(IS31FL3743A_ENABLE_GPIO);
#endif
    gpio_set_pin_input(SLEEP_GPIO);

    keyboard_pre_init_user();
}

/**
 * Called by QMK when the keyboard suspends
 */
void suspend_power_down_kb(void) {
    is_suspended = true;

#ifdef RGB_MATRIX_ENABLE
#    ifndef NO_SUSPEND_POWER_DOWN
    gpio_write_pin_low(IS31FL3743A_ENABLE_GPIO);
#    endif
#endif

    suspend_power_down_user();
}

/**
 * Called by QMK when the keyboard wakes up from suspend
 */
void suspend_wakeup_init_kb(void) {
    is_suspended = false;

#ifdef RGB_MATRIX_ENABLE
#    ifndef NO_SUSPEND_POWER_DOWN
    gpio_write_pin_high(IS31FL3743A_ENABLE_GPIO);
#    endif
#endif

    suspend_wakeup_init_user();
}

// If in BIOS mode, no matter what the keys have been remapped to, always send them as the F keys
bool bios_mode = true;

void set_bios_mode(bool val) {
    bios_mode = val;

#ifdef BIOS_HOTKEY_DEBUG
    if (bios_mode) {
        // Red
#    if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_sethsv_noeeprom(0, 0xFF, 0xFF);
        rgb_matrix_mode_noeeprom(1);
#    endif
        gpio_write_pin(GP24, 1);
    } else {
        // White
#    if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_sethsv_noeeprom(0, 0, 0xFF);
        rgb_matrix_mode_noeeprom(1);
#    endif
        gpio_write_pin(GP24, 0);
    }
#endif
}
typedef struct {
    keypos_t position;
    uint8_t  keycode;
} bios_hotkey_t;

static const bios_hotkey_t bios_hotkeys[] = {
    {.position = {.row = 3, .col = 5}, .keycode = KC_F1}, {.position = {.row = 2, .col = 5}, .keycode = KC_F2}, {.position = {.row = 6, .col = 4}, .keycode = KC_F3}, {.position = {.row = 3, .col = 4}, .keycode = KC_F4}, {.position = {.row = 4, .col = 10}, .keycode = KC_F5}, {.position = {.row = 3, .col = 10}, .keycode = KC_F6}, {.position = {.row = 2, .col = 10}, .keycode = KC_F7}, {.position = {.row = 1, .col = 15}, .keycode = KC_F8}, {.position = {.row = 3, .col = 11}, .keycode = KC_F9}, {.position = {.row = 4, .col = 8}, .keycode = KC_F10}, {.position = {.row = 6, .col = 8}, .keycode = KC_F11}, {.position = {.row = 3, .col = 13}, .keycode = KC_F12},
};

static bool handle_bios_hotkeys(keyrecord_t *record) {
    if (!bios_mode) {
        return true;
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(bios_hotkeys); i++) {
        const bios_hotkey_t *hotkey = &bios_hotkeys[i];
        if (record->event.key.row != hotkey->position.row || record->event.key.col != hotkey->position.col) {
            continue;
        }

        if (record->event.pressed) {
            register_code(hotkey->keycode);
        } else {
            unregister_code(hotkey->keycode);
        }
        return false;
    }

    return true;
}

bool process_detected_host_os_kb(os_variant_t os) {
    set_bios_mode(os != OS_LINUX && os != OS_WINDOWS);
    keymap_config.nkro = !bios_mode;

#if defined(OS_DETECTION_RGB_DEBUG) && defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(1);
    switch (os) {
        case OS_UNSURE:
            rgb_matrix_sethsv(0, 0, 255); // White
            break;
        case OS_LINUX:
            rgb_matrix_sethsv(213, 255, 255); // Purple
            break;
        case OS_WINDOWS:
            rgb_matrix_sethsv(170, 255, 255); // Blue
            break;
        case OS_MACOS:
            rgb_matrix_sethsv(85, 255, 255); // Green
            break;
        case OS_IOS:
            rgb_matrix_sethsv(43, 255, 255); // Yellow
            break;
        default:
            rgb_matrix_sethsv(125, 255, 255); // Cyan
            break;
    }
#endif

    return process_detected_host_os_user(os);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (!handle_bios_hotkeys(record)) {
        return false;
    }

#ifdef RGB_MATRIX_ENABLE
    uint8_t h;
    uint8_t s;
    uint8_t v;
    uint8_t new_v;
#endif

    switch (keycode) {
        // Implement step brightness for RGB backlight
#ifdef RGB_MATRIX_ENABLE
        case QK_RGB_MATRIX_MODE_NEXT:
        case QK_RGB_MATRIX_MODE_PREVIOUS:
            // Turn on if it was off
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_enable();
            }
            return true;
        case BL_STEP:
            if (record->event.pressed) {
                h = rgb_matrix_get_hue();
                s = rgb_matrix_get_sat();
                v = rgb_matrix_get_val();
                switch (v) {
                    default: // Default when user set to a different level
                    case 0:
                        new_v = 85;
                        break;
                    case 85:
                        new_v = 170;
                        break;
                    case 170:
                        new_v = 255;
                        break;
                    case 255:
                        new_v = 0;
                        break;
                }
                rgb_matrix_sethsv(h, s, new_v);
            }
            return true;
#endif
        case FW_SCRN:
            // Simulate press WIN+P
            // Works (at least) on Windows and GNOME
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_P);
            } else {
                unregister_code(KC_P);
                unregister_code(KC_LGUI);
            }
            return false; // Skip all further processing of this key
        case FW_AIRP:
            if (record->event.pressed) {
                host_radio_send();
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}

#ifdef BIOS_HOTKEY_DEBUG
// Ignore capslock updates in order to manually control it
bool led_update_kb(led_t led_state) {
    (void)led_state;
    return false;
}
#endif
