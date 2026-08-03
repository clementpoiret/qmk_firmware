// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// The serial number is written to the final 4 KiB block in the first MiB.
#define FLASH_OFFSET 0x10000000UL
#define LAST_4K_BLOCK 0xFF000UL
#define SERIALNUM_LEN 18

// 18-character fallback serial for an ANSI RGB keyboard.
#define FALLBACK_SERIAL_NUMBER L"FRAKDKEN0100000000"
#define FALLBACK_SERIAL_NUMBER_ASCII "FRAKDKEN0100000000"

_Static_assert(sizeof(FALLBACK_SERIAL_NUMBER) == (SERIALNUM_LEN + 1) * 2, "Fallback serial number must be the expected length");

extern char ascii_serialnum[SERIALNUM_LEN + 1];
