// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_COLS 16
#define MATRIX_ROWS 8

#define IS31FL3743A_I2C_ADDRESS_1 IS31FL3743A_I2C_ADDRESS_GND_GND
#define IS31FL3743A_I2C_ADDRESS_2 IS31FL3743A_I2C_ADDRESS_GND_VCC
#define RGB_MATRIX_LED_COUNT 97
#define IS31FL3743A_CONFIGURATION 0x21 // Enable only the first 9 SW and disable software shutdown

// Limit current to ensure max current draw is just about 500mA
// when white att 100% brightness
#define IS31FL3743A_GLOBAL_CURRENT 104
