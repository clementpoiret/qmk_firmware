BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm

OS_DETECTION_ENABLE = yes

CUSTOM_MATRIX = lite
SRC += matrix.c analog.c
SRC += dyn_serial.c

# Expose the Framework airplane-mode key as an opt-in HID report.
OPT_DEFS += -DWIRELESS_RADIO_ENABLE
