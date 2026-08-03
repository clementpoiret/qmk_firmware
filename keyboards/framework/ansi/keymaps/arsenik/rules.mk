# Keep the source keymap authoritative; the vendor default remains available
# when live VIA remapping is required.
VIA_ENABLE = no
RAW_ENABLE = yes

MOUSEKEY_ENABLE = yes
REPEAT_KEY_ENABLE = yes
CAPS_WORD_ENABLE = no

# Preserve Framework's factory Raw HID protocol without enabling VIA.
SRC += keyboards/framework/factory.c
