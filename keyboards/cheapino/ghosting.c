// Copyright 2024 Thomas Haukland (@tompi)
// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ghosting.h"

#include <stdbool.h>
#include <stdint.h>

#include "util.h"

#ifdef CONSOLE_ENABLE
#    include "debug.h"
#    include "print.h"
#endif

typedef struct {
    matrix_row_t cause;
    matrix_row_t observed;
    matrix_row_t phantom;
} ghost_pattern_t;

// These ten rules preserve the Cheapino v2 patterns observed by the original
// firmware. Each rule is mirrored to the left-hand columns by shifting six
// positions. The scanner cannot distinguish a phantom from the same complete
// matrix state produced by legitimate switches.
static const ghost_pattern_t ghost_patterns[] = {
    {.cause = 0x006, .observed = 0x005, .phantom = 0x004},
    {.cause = 0x006, .observed = 0x00A, .phantom = 0x002},
    {.cause = 0x018, .observed = 0x014, .phantom = 0x010},
    {.cause = 0x018, .observed = 0x028, .phantom = 0x008},
    {.cause = 0x021, .observed = 0x011, .phantom = 0x001},
    {.cause = 0x021, .observed = 0x022, .phantom = 0x020},
    {.cause = 0x009, .observed = 0x00A, .phantom = 0x008},
    {.cause = 0x009, .observed = 0x005, .phantom = 0x001},
    {.cause = 0x012, .observed = 0x022, .phantom = 0x002},
    {.cause = 0x012, .observed = 0x011, .phantom = 0x010},
};

static bool has_all_bits(matrix_row_t value, matrix_row_t pattern) {
    return (value & pattern) == pattern;
}

static void apply_ghost_pattern(matrix_row_t matrix[], uint8_t pattern_id, uint8_t row_offset, uint8_t column_shift) {
    const ghost_pattern_t *pattern  = &ghost_patterns[pattern_id];
    const matrix_row_t     cause    = pattern->cause << column_shift;
    const matrix_row_t     observed = pattern->observed << column_shift;
    const matrix_row_t     phantom  = pattern->phantom << column_shift;

    for (uint8_t cause_row = 0; cause_row < 3; cause_row++) {
        const uint8_t absolute_cause_row = row_offset + cause_row;
        if (!has_all_bits(matrix[absolute_cause_row], cause)) {
            continue;
        }

        for (uint8_t row_delta = 1; row_delta < 3; row_delta++) {
            const uint8_t observed_row          = (cause_row + row_delta) % 3;
            const uint8_t absolute_observed_row = row_offset + observed_row;
            if (!has_all_bits(matrix[absolute_observed_row], observed)) {
                continue;
            }

            matrix[absolute_observed_row] &= ~phantom;
#ifdef CONSOLE_ENABLE
            if (debug_enable && debug_matrix) {
                dprintf("cheapino ghost: pattern=%u side=%c cause=r%u observed=r%u clear=%04X\n", pattern_id + 1, row_offset == 0 ? 'R' : 'L', absolute_cause_row, absolute_observed_row, phantom);
            }
#endif
        }
    }
}

void cheapino_suppress_ghosts(matrix_row_t matrix[]) {
    for (uint8_t pattern_id = 0; pattern_id < ARRAY_SIZE(ghost_patterns); pattern_id++) {
        apply_ghost_pattern(matrix, pattern_id, 0, 0);
        apply_ghost_pattern(matrix, pattern_id, 4, 6);
    }
}
