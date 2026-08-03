// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum framework_keycodes {
    // Switch display modes by sending GUI+P.
    FW_SCRN = SAFE_RANGE,
    FW_FN_LOCK,
    FW_AIRP,
};

extern bool bios_mode;
extern bool is_suspended;

// Uncomment this to show hotkey mode with capslock LED and backlight
// hotkey mode on:  capslock ON,  RGB red
// hotkey mode off: capslock OFF, RGB white
// #define BIOS_HOTKEY_DEBUG
void set_bios_mode(bool val);

#define SLEEP_GPIO GP0
#define MUX_ENABLE_GPIO GP4
#define BOOT_DONE_GPIO GP5
// Pin SDB to enable the RGB controller
#define IS31FL3743A_ENABLE_GPIO GP29
