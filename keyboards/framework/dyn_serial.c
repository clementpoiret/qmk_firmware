// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "dyn_serial.h"
#include "usb_descriptor.h"
#include "usb_descriptor_common.h"

USB_Descriptor_String_t PROGMEM SerialNumberString = {.Header = {.Size = sizeof(FALLBACK_SERIAL_NUMBER), .Type = DTYPE_String}, .UnicodeString = FALLBACK_SERIAL_NUMBER};

char ascii_serialnum[SERIALNUM_LEN + 1] = FALLBACK_SERIAL_NUMBER_ASCII;

typedef struct PACKED {
    uint8_t revision;
    uint8_t serialnum[SERIALNUM_LEN];
    uint8_t crc32[4];
} serialnum_raw_t;

static uint32_t crc32b(const uint8_t *message, size_t message_length) {
    uint32_t crc = UINT32_MAX;

    for (size_t i = 0; i < message_length; i++) {
        crc ^= message[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            uint32_t mask = -(crc & 1U);
            crc           = (crc >> 1) ^ (0xEDB88320UL & mask);
        }
    }

    return ~crc;
}

const void *usb_descriptor_get_serial_number(void) {
    const serialnum_raw_t *record = (const serialnum_raw_t *)(FLASH_OFFSET + LAST_4K_BLOCK);

    if (record->revision != 1) {
        return &SerialNumberString;
    }

    uint32_t expected_crc = ((uint32_t)record->crc32[3] << 24) | ((uint32_t)record->crc32[2] << 16) | ((uint32_t)record->crc32[1] << 8) | record->crc32[0];
    uint32_t actual_crc   = crc32b((const uint8_t *)record, SERIALNUM_LEN + 1);
    if (expected_crc != actual_crc) {
        return &SerialNumberString;
    }

    for (uint8_t i = 0; i < SERIALNUM_LEN; i++) {
        if (record->serialnum[i] > 0x7F) {
            dprintf("Serial number character %u is not valid ASCII.\n", record->serialnum[i]);
            return &SerialNumberString;
        }
    }

    memcpy(ascii_serialnum, record->serialnum, SERIALNUM_LEN);
    for (uint8_t i = 0; i < SERIALNUM_LEN; i++) {
        SerialNumberString.UnicodeString[i] = ascii_serialnum[i];
    }

    return &SerialNumberString;
}

uint16_t usb_descriptor_get_serial_number_size(void) {
    return pgm_read_byte(&SerialNumberString.Header.Size);
}
