# Copyright 2026 Clement Poiret (@clementpoiret)
# SPDX-License-Identifier: GPL-2.0-or-later

ENCODER_ENABLE = yes
ENCODER_DRIVER = custom

VPATH += keyboards/cheapino
SRC += keyboards/cheapino/ghosting.c
SRC += keyboards/cheapino/matrix_encoder.c
