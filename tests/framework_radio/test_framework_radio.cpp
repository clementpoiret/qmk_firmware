// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test_common.hpp"

TEST(FrameworkRadio, SendsWirelessRadioButtonReport) {
    TestDriver driver;

    EXPECT_CALL(driver, send_extra_mock(testing::Truly([](const report_extra_t &report) { return report.report_id == REPORT_ID_RADIO && report.usage == 1; })));

    host_radio_send();
    VERIFY_AND_CLEAR(driver);
}
