# Framework Laptop 16 Arsenik keymap

This source-authoritative keymap adapts the Cheapino and Corne Arsenik
behavior to the Framework Laptop 16 ANSI keyboard. It assumes Linux XKB
Ergo-L 1.0.0 and `compose:menu`: the base layer sends positional QWERTY HID
usages, while non-base shortcuts and punctuation use semantic Ergo-L aliases.

VIA is intentionally disabled for this keymap. The Framework factory Raw HID
protocol, serial number, media keys, display switching, airplane-mode key,
RGB Matrix, and white backlight remain available.

## Build

```sh
qmk compile -kb framework/ansi -km arsenik
```

The deployable image is `.build/framework_ansi_arsenik.uf2`, also copied to
the repository root as `framework_ansi_arsenik.uf2`.

## Layers and access

| Layer | Access | Purpose |
| --- | --- | --- |
| `BASE` | Default | Ergo-L positional typing, home-row mods, and the media-first top row |
| `NAV` | Hold Caps Lock or physical left Alt; tapping either sends Escape | Navigation, editing, browser actions, and Repeat |
| `NUM_EDIT` | Hold physical right Ctrl; tap sends Enter | Right-hand digits and arithmetic with left-hand navigation/editing |
| `MOUSE` | Hold physical left GUI; tap sends Tab | Pointer movement, scrolling, buttons, and speed selection |
| `FW` | Hold physical Fn | F1-F12, lighting, Framework controls, Compose, and layer locks |

Caps Lock also acts as Escape/NAV: tap it for Escape or hold it for `NAV`. The
bottom row retains a second Escape/NAV access key:

```text
LCtrl  Fn/FW  Tab/MOUSE  Esc/NAV  Space  AltGr  Enter/NUM_EDIT  Left Up Down Right
```

`NUM_EDIT` and `MOUSE` can be toggled with `Fn+H` and `Fn+;`. The access key
for a locked layer unlocks it. Locked layers have no timeout.

## Base and home-row mods

The alpha block emits raw positional QWERTY usages. Linux XKB Ergo-L produces:

```text
Q       C       O        P       W      | J       M        D        ODK     Y
A/GUI   S/Alt   E/Shift  N/Ctrl  F      | L       R/Ctrl   T/Shift  I/Alt   U/GUI
Z       X       -        V       B      | .       H        G        ,       K
```

The top row remains media-first. Hold Fn for F1-F12; Fn+Delete sends Insert.
There is no persistent Fn lock.

## NAV

```text
Ctrl+Left        Ctrl+Right        Ctrl+Bsp   Ctrl+Del   Repeat | BrowserBack Home PgDn PgUp End
Ctrl+A           Ctrl+Z            Redo       Ctrl+C     Ctrl+V | BrowserFwd  Left Down Up   Right
Ctrl+Shift+Left  Ctrl+Shift+Right  Shift+Home Shift+End Ctrl+X | x            PrevTab NextTab x x
```

Redo is `Ctrl+Shift+Z`; previous and next tab are `Ctrl+Shift+Tab` and
`Ctrl+Tab`.

## NUM_EDIT

```text
=     Home       Up        End       PgUp       | /  7 8 9 *
+     Left       Down      Right     PgDn       | -  4 5 6 0
ODK   Ctrl+Left  Ctrl+Bsp  Ctrl+Del  Ctrl+Right | ,  1 2 3 .
```

The layer uses digit-row HID usages rather than keypad keycodes. Its bottom
controls provide Tab, Backspace, Enter, and the layer unlock.

## MOUSE

```text
Slow  Fast  x    x    x | Button4 WheelLeft WheelDown WheelUp WheelRight
Ctrl  Shift Alt  GUI  x | Button5 Left      Down      Up      Right
Btn1  Btn2  Btn3 x    x | x       x         x         x       x
```

The bottom controls provide Base exit, layer unlock, Space, Backspace, and
Escape. Slow and Fast use QMK Mouse Keys acceleration levels 0 and 2.

## FW controls

- The top row sends F1-F12, with Insert on Delete.
- `W/E/R/T/Y/U/I` control RGB toggle, effect, hue, saturation, speed, value,
  and speed down; `D/F/G/J` provide the corresponding previous/down actions.
- `O/P` send Caps Lock and Application/Compose.
- `H/;` toggle `NUM_EDIT` and `MOUSE`.
- `[/K/B` send Pause, Scroll Lock, and Break.
- `C/Space` control backlight breathing and brightness stepping.
- The arrow cluster sends Home, Page Up, Page Down, and End.

Active keys are overlaid in blue for `NAV`, green for `NUM_EDIT`, magenta for
`MOUSE`, and yellow for `FW`; all other LEDs retain the selected RGB effect.

## Tap-hold policy

| Key class | Tapping term | Quick tap | Decision policy |
| --- | --- | --- | --- |
| Eight home-row mods | 200 ms | 175 ms | Flow Tap plus opposite-hand Chordal Hold |
| Escape/NAV (Caps and left Alt), Tab/MOUSE, Enter/NUM_EDIT | 150 ms | Disabled | Hold on another key press, either hand |

The four layer-tap positions and Space are neutral in the Chordal Hold hand
map. The number-row `6` is left-hand and `7` is right-hand.

## Bootloader

The firmware does not expose `QK_BOOT`. Use the Framework hardware procedure:
power off, remove the keyboard module, hold the physical left Alt and right Alt
positions while reinstalling it, then copy `framework_ansi_arsenik.uf2` to the
RP2040 mass-storage device.
