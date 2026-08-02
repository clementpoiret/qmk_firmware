// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <array>
#include <vector>

#include "gtest/gtest.h"

extern "C" {
#include "encoder.h"
#include "ghosting.h"
#include "matrix_encoder.h"
#include "test_matrix.h"
}

namespace {

struct GhostPattern {
    matrix_row_t cause;
    matrix_row_t observed;
    matrix_row_t phantom;
};

constexpr std::array<GhostPattern, 10> ghost_patterns = {{
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
}};

std::vector<bool> button_updates;

void feed_encoder_state(uint8_t state) {
    matrix_row_t raw_matrix[MATRIX_ROWS] = {};
    if (state & 1U) {
        raw_matrix[3] |= (matrix_row_t)1U << 2;
    }
    if (state & 2U) {
        raw_matrix[3] |= (matrix_row_t)1U << 4;
    }
    cheapino_encoder_capture(raw_matrix);
    encoder_driver_task();
}

void expect_single_encoder_event(bool clockwise) {
    uint8_t event_index;
    bool    event_clockwise;

    ASSERT_TRUE(encoder_dequeue_event(&event_index, &event_clockwise));
    EXPECT_EQ(event_index, 0);
    EXPECT_EQ(event_clockwise, clockwise);
    EXPECT_FALSE(encoder_dequeue_event(&event_index, &event_clockwise));
}

class CheapinoInternals : public ::testing::Test {
   protected:
    void SetUp() override {
        clear_all_keys();
        button_updates.clear();
        encoder_init();
    }

    void TearDown() override {
        clear_all_keys();
    }
};

TEST_F(CheapinoInternals, PreservesAllObservedGhostRulesOnBothHands) {
    for (uint8_t side = 0; side < 2; side++) {
        const uint8_t row_offset   = side == 0 ? 0 : 4;
        const uint8_t column_shift = side == 0 ? 0 : 6;

        for (uint8_t pattern_id = 0; pattern_id < ghost_patterns.size(); pattern_id++) {
            SCOPED_TRACE(::testing::Message() << "side=" << +side << " pattern=" << +pattern_id);
            const GhostPattern &pattern = ghost_patterns[pattern_id];
            matrix_row_t         matrix[MATRIX_ROWS] = {};
            matrix[row_offset]     = pattern.cause << column_shift;
            matrix[row_offset + 1] = pattern.observed << column_shift;

            cheapino_suppress_ghosts(matrix);

            EXPECT_EQ(matrix[row_offset], pattern.cause << column_shift);
            EXPECT_EQ(matrix[row_offset + 1], (pattern.observed & ~pattern.phantom) << column_shift);
        }
    }
}

TEST_F(CheapinoInternals, GhostSuppressionPreservesUnrelatedBits) {
    matrix_row_t matrix[MATRIX_ROWS] = {};
    matrix[0] = 0x006;
    matrix[1] = 0x005 | 0x800;
    matrix[2] = 0x400;

    cheapino_suppress_ghosts(matrix);

    EXPECT_EQ(matrix[0], 0x006);
    EXPECT_EQ(matrix[1], 0x001 | 0x800);
    EXPECT_EQ(matrix[2], 0x400);
}

TEST_F(CheapinoInternals, AmbiguousLegitimateStateIsStillSuppressed) {
    matrix_row_t matrix[MATRIX_ROWS] = {};
    matrix[0] = 0x006;
    matrix[1] = 0x005;

    cheapino_suppress_ghosts(matrix);

    // Firmware cannot distinguish a real key at this bit from the observed
    // phantom, so preserving the historical policy necessarily drops it.
    EXPECT_EQ(matrix[1], 0x001);
}

TEST_F(CheapinoInternals, EncoderCaptureMasksOnlyQuadratureBits) {
    matrix_row_t matrix[MATRIX_ROWS] = {};
    matrix[3] = ((matrix_row_t)1U << 0) | ((matrix_row_t)1U << 2) | ((matrix_row_t)1U << 4) | ((matrix_row_t)1U << 7);

    cheapino_encoder_capture(matrix);

    EXPECT_EQ(matrix[3], ((matrix_row_t)1U << 0) | ((matrix_row_t)1U << 7));
}

TEST_F(CheapinoInternals, EmitsOneClockwiseEventForACompleteCycle) {
    for (uint8_t state : {0, 2, 3, 1, 0}) {
        feed_encoder_state(state);
    }
    expect_single_encoder_event(true);
}

TEST_F(CheapinoInternals, EmitsOneCounterClockwiseEventForACompleteCycle) {
    for (uint8_t state : {0, 1, 3, 2, 0}) {
        feed_encoder_state(state);
    }
    expect_single_encoder_event(false);
}

TEST_F(CheapinoInternals, BounceAndRepeatedStatesDoNotDuplicateEvents) {
    for (uint8_t state : {0, 2, 2, 0, 0, 2, 3, 3, 1, 0}) {
        feed_encoder_state(state);
    }
    expect_single_encoder_event(true);
}

TEST_F(CheapinoInternals, InvalidTransitionClearsPartialMovement) {
    for (uint8_t state : {0, 2, 1, 0}) {
        feed_encoder_state(state);
    }

    uint8_t event_index;
    bool    event_clockwise;
    EXPECT_FALSE(encoder_dequeue_event(&event_index, &event_clockwise));

    for (uint8_t state : {2, 3, 1, 0}) {
        feed_encoder_state(state);
    }
    expect_single_encoder_event(true);
}

TEST_F(CheapinoInternals, SkippedStatesDoNotEmitMovement) {
    for (uint8_t state : {0, 3, 0}) {
        feed_encoder_state(state);
    }

    uint8_t event_index;
    bool    event_clockwise;
    EXPECT_FALSE(encoder_dequeue_event(&event_index, &event_clockwise));
}

TEST_F(CheapinoInternals, BothContactsToNeutralClearsPartialMovement) {
    for (uint8_t state : {0, 2, 3, 0}) {
        feed_encoder_state(state);
    }

    uint8_t event_index;
    bool    event_clockwise;
    EXPECT_FALSE(encoder_dequeue_event(&event_index, &event_clockwise));

    for (uint8_t state : {2, 3, 1, 0}) {
        feed_encoder_state(state);
    }
    expect_single_encoder_event(true);
}

TEST_F(CheapinoInternals, EncoderButtonReportsStableEdgesOnce) {
    cheapino_encoder_button_task();
    press_key(0, 3);
    cheapino_encoder_button_task();
    cheapino_encoder_button_task();
    release_key(0, 3);
    cheapino_encoder_button_task();
    cheapino_encoder_button_task();

    ASSERT_EQ(button_updates.size(), 2);
    EXPECT_TRUE(button_updates[0]);
    EXPECT_FALSE(button_updates[1]);
}

} // namespace

extern "C" bool cheapino_encoder_button_update_user(bool pressed) {
    button_updates.push_back(pressed);
    return false;
}
