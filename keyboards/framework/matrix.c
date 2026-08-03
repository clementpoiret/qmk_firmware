// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>

#include "analog.h"
#include "hal_adc.h"
#include "framework.h"
#include "quantum.h"

typedef int32_t adc10ksample_t;

// Mux GPIOs
#define MUX_A GP1
#define MUX_B GP2
#define MUX_C GP3

#define ADC_CH2_PIN GP28
#define PAL_MODE_ADC_PULLUP (PAL_MODE_INPUT_ANALOG | PAL_RP_PAD_PUE)

// Voltage threshold - anything below that counts as pressed
// 29000 = 2.9V * 10000
static const adc10ksample_t ADC_THRESHOLD            = 29000;
static const pin_t          column_pins[MATRIX_COLS] = {GP8, GP9, GP10, GP11, GP12, GP13, GP14, GP15, GP21, GP20, GP19, GP18, GP17, GP16, GP23, GP22};
static const uint8_t        mux_indices[MATRIX_ROWS] = {2, 0, 1, 3, 4, 5, 6, 7};

static bool prev_lid_closed = false;

static adc10ksample_t to_voltage(adcsample_t sample) {
    int voltage = sample * 33000;
    return voltage / 1023;
}

static void print_as_float(adc10ksample_t sample) {
    int digits   = sample / 10000;
    int decimals = sample % 10000;
    uprintf("%d.%02d\n", digits, decimals);
}

/**
 * Tell RP2040 ADC controller to initialize a specific GPIO for ADC input
 */
static void framework_adc_gpio_init(int gpio) {
    assert(gpio >= GP26 && gpio <= GP28);
    // Keep rows without an external pull-up from floating.
    palSetLineMode(gpio, PAL_MODE_ADC_PULLUP);
}

/**
 * Tell the mux to select a specific column
 *
 * Splits the positive integer (<=7) into its three component bits.
 */
static void mux_select_row(int row) {
    assert(row >= 0 && row < MATRIX_ROWS);

    uint8_t mux_index = mux_indices[row];
    gpio_write_pin(MUX_A, mux_index & 0x01);
    gpio_write_pin(MUX_B, mux_index & 0x02);
    gpio_write_pin(MUX_C, mux_index & 0x04);
}

/**
 * Based on the ADC value, update the matrix for this column
 * */
static bool interpret_adc_row(matrix_row_t cur_matrix[], adc10ksample_t voltage, int col, int row, adc10ksample_t threshold) {
    // By default the voltage is high (3.3V)
    // When a key is pressed it causes the voltage to go down.
    // But because every key is connected in a matrix, pressing multiple keys
    // changes the voltage at every key again. So we can't check for a specific
    // voltage but need to have a threshold.
    bool key_state = voltage < threshold;

    if (key_state) {
        uprintf("Col %d - Row %d - State: %d, Voltage: ", col, row, key_state);
        print_as_float(voltage);
    }

    matrix_row_t new_row = cur_matrix[row];
    if (key_state) {
        new_row |= (matrix_row_t)1U << col;
    } else {
        new_row &= ~((matrix_row_t)1U << col);
    }
    bool changed = cur_matrix[row] != new_row;
    if (key_state) {
        uprintf("Keypress at KSO%d, KSI%d - %d.%dV\n", col, row, (int)(voltage / 10000), (int)(voltage % 10000));
    }
    cur_matrix[row] = new_row;

    return changed;
}

/**
 * Drive the GPIO for a column low or high.
 */
static void drive_col(int col, bool high) {
    assert(col >= 0 && col < MATRIX_COLS);
    if (high) {
        gpio_write_pin_high(column_pins[col]);
    } else {
        gpio_write_pin_low(column_pins[col]);
    }
}

/**
 * Read a value from the ADC and print some debugging details
 */
static adc10ksample_t read_adc(void) {
    // analogReadPin() would remove the internal pull-up configured at init.
    uint16_t val = adc_read(pinToMux(ADC_CH2_PIN));
    return to_voltage(val);
}

/**
 * Handle the host going to sleep or the keyboard being idle
 * TODO: If the host is asleep the keyboard should reduce the scan rate and turn backlight off.
 *
 * TODO: If the host is awake but the keyboard is idle it should enter a low-power state
 */
static bool handle_lid_state(void) {
    bool lid_closed  = !gpio_read_pin(SLEEP_GPIO);
    bool lid_changed = lid_closed != prev_lid_closed;
    prev_lid_closed  = lid_closed;

    /* If lid is closed and the keyboard is not currently suspended, we need to
     * suspend the keyboard.
     *
     * This does not normally happen, unless the user has configured their OS
     * to not suspend if lid is closed.
     *
     * There is no case where the lid is closed that the keyboard should stay active.
     **/
    if (lid_closed && !is_suspended) {
        suspend_power_down();
    }

    /* If the lid is open and the system is transitioning between sleep states,
     * QMK automatically handles suspending by monitoring USB suspend state.
     *
     * The only case where we need custom behavior is when the system was awake
     * with lid closed and then the lid is opened. In this case we need to wake
     * the keyboard.
     */
    if (!lid_closed && lid_changed) {
        suspend_wakeup_init();
    }

    // Ignore keypresses if lid closed
    return lid_closed;
}

/**
 * Overriding behavior of matrix_scan from quantum/matrix.c
 */
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    adc10ksample_t voltages[MATRIX_ROWS][MATRIX_COLS] = {};

    /* If lid is closed, ignore keypresses. Otherwise pressing on the lid (e.g. in
     * a backpack) might cause the system to wake up.
     **/
    if (handle_lid_state()) {
        return false;
    }

    // Drive all high to deselect them.
    for (int col = 0; col < MATRIX_COLS; col++) {
        drive_col(col, true);
    }

    // Go through every matrix column (KSO) and drive them low individually
    // Then go through every matrix row (KSI), select it with the mux and check their ADC value
    for (int col = 0; col < MATRIX_COLS; col++) {
        // Drive column low so we can measure the resistors on each row in this column
        drive_col(col, false);
        for (int row = 0; row < MATRIX_ROWS; row++) {
            mux_select_row(row);
            voltages[row][col] = read_adc();
        }

        // Drive column high again
        drive_col(col, true);
    }

    for (int row = 0; row < MATRIX_ROWS; row++) {
        uint8_t pressed_in_row = 0;
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (voltages[row][col] < ADC_THRESHOLD) {
                pressed_in_row += 1;
            }
        }
        for (int col = 0; col < MATRIX_COLS; col++) {
            adc10ksample_t threshold = ADC_THRESHOLD;
            switch (pressed_in_row) {
                case 0:
                case 1:
                    threshold = 10000; // 1.0V
                    break;
                case 2:
                    threshold = 20000; // 2.0V
                    break;
                case 3:
                    threshold = 25000; // 2.5V
                    break;
                default:
                    threshold = ADC_THRESHOLD;
                    break;
            }
            // Interpret ADC value as rows
            changed |= interpret_adc_row(current_matrix, voltages[row][col], col, row, threshold);
        }
    }

    return changed;
}

/**
 * Enable the ADC MUX
 *
 * TODO: Do we need a de-init? Probably not.
 */
static void adc_mux_init(void) {
    gpio_set_pin_output(MUX_ENABLE_GPIO);
    gpio_write_pin_low(MUX_ENABLE_GPIO);

    gpio_set_pin_output(MUX_A);
    gpio_set_pin_output(MUX_B);
    gpio_set_pin_output(MUX_C);
}

/**
 * Overriding behavior of matrix_init from quantum/matrix.c
 */
void matrix_init_custom(void) {
    adc_mux_init();
    framework_adc_gpio_init(ADC_CH2_PIN);

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        gpio_set_pin_output(column_pins[col]);
    }

    // Set unused pins to input to avoid interfering. They're hooked up to rows 5 and 6
    gpio_set_pin_input(GP6);
    gpio_set_pin_input(GP7);
}
