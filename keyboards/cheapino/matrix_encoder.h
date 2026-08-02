// Copyright 2026 Clement Poiret (@clementpoiret)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>

#include "matrix.h"

void cheapino_encoder_capture(matrix_row_t current_matrix[]);
void cheapino_encoder_button_task(void);

bool cheapino_encoder_button_update_kb(bool pressed);
bool cheapino_encoder_button_update_user(bool pressed);
