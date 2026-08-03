# Framework Laptop 16 ANSI keyboard

Firmware for the standard 78-key ANSI Framework Laptop 16 keyboard input
module (right Ctrl, USB VID `0x32AC`, PID `0x0012`). This is a forward-port of
Framework's v0.3.1 firmware to the QMK version in this repository.

- Maintainer: [Daniel Schaefer](https://github.com/JohnAZoidberg)
- Hardware: [Framework Laptop 16 keyboard](https://frame.work/products/laptop16-diy-amd-7040)
- Vendor source: [Framework QMK v0.3.1](https://github.com/FrameworkComputer/qmk_firmware/tree/v0.3.1/keyboards/framework)

This target is not compatible with the Copilot, ISO, JIS, numpad, or macropad
input modules.

## Available keymaps

| Keymap | Intended use | Remapping |
| --- | --- | --- |
| `default` | Framework's media-first layout, Fn controls, and persistent Fn Lock | VIA, with ten dynamic layers |
| `arsenik` | Ergo-L-oriented layout matching the Cheapino v2 and Corne: home-row mods, navigation, numeric editing, and mouse layers | Source-authoritative; VIA disabled |

Build either keymap with:

```sh
qmk compile -kb framework/ansi -km default
qmk compile -kb framework/ansi -km arsenik
```

The deployable images are `.build/framework_ansi_default.uf2` and
`.build/framework_ansi_arsenik.uf2`. QMK also copies the selected image to the
repository root.

## Shared top row

Both keymaps keep the released media-first top row during normal OS use:

```text
Esc | Mute Vol- Vol+ Previous Play/Pause Next Brightness- Brightness+
    | Display Airplane PrintScreen MediaSelect Delete
```

Hold the physical Fn key to turn the twelve middle positions into F1-F12 and
Delete into Insert. The special Framework keys behave as follows:

- **Display** sends `Super+P` (`Win+P`), which opens display switching on
  Windows and GNOME.
- **Airplane** sends the USB Wireless Radio HID report. Whether it changes
  airplane mode depends on host support.
- **Brightness-** and **Brightness+** send standard display-brightness HID
  usages; they do not control the keyboard LEDs.

### BIOS-safe function keys

The keyboard starts in BIOS mode, where the twelve physical top-row positions
always send F1-F12 regardless of keymap or VIA remapping. This keeps firmware
setup and boot hotkeys reachable. After QMK detects Linux or Windows, it
enables the normal media-first layout and NKRO. Unknown hosts, macOS, and iOS
remain in the conservative BIOS mode with NKRO disabled.

## RGB Matrix and backlight controls

The keyboard has a 97-LED per-key RGB Matrix plus a separate single-zone PWM
backlight. The RGB controls are on the Fn layer:

| Action | `default` | `arsenik` |
| --- | --- | --- |
| Toggle RGB | Fn+W | Fn+W |
| Next pattern | Fn+E | Fn+E |
| Previous pattern | Fn+D | Fn+D |
| Hue up / down | Fn+R / Fn+F | Fn+R / Fn+F |
| Saturation up / down | Fn+T / Fn+G | Fn+T / Fn+G |
| Animation speed up / down | Fn+Y / Fn+H | Fn+Y / Fn+I |
| Brightness up / down | Fn+U / Fn+J | Fn+U / Fn+J |
| Step brightness through 0%, 33%, 67%, 100% | Fn+Space | Fn+Space |
| Toggle single-zone backlight breathing | Fn+C | Fn+C |

To change the color pattern, hold Fn and tap E repeatedly; Fn+D walks backward
through the list. Selecting either direction also turns RGB back on if it was
disabled. Solid, gradient, breathing, band, cycle, rainbow, raindrop, pixel,
typing-heatmap, digital-rain, reactive, and splash families are compiled in.
Hue affects fixed-color patterns, while saturation and animation speed only
produce a visible change in effects that use those parameters.

The RGB controller runs above the audible range, total LED current is limited
to approximately 500 mA at full white, and the controller powers down during
USB suspend.

## Default keymap

The default base layer is a conventional ANSI layout with the shared
media-first top row. Hold Fn for these additional controls:

```text
Top row: Fn Lock | F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12 | Insert
Letters: W/E/R/T/Y/U = RGB toggle/next/hue+/sat+/speed+/brightness+
         D/F/G/H/J   = RGB previous/hue-/sat-/speed-/brightness-
         P/K/B       = Pause/Scroll Lock/Break
         C/Space     = backlight breathing/RGB brightness step
Arrows:  Left/Up/Down/Right = Home/Page Up/Page Down/End
```

Fn+Esc enables Fn Lock persistently, including across resets. In Fn Lock:

- the top row sends F1-F12 without holding Fn;
- holding Fn temporarily restores the media/system row and lighting controls;
- Fn+Esc disables Fn Lock and returns to the media-first base layer.

VIA is enabled for `default`, including EEPROM reset and ten dynamic layers.

## Arsenik keymap

The Arsenik keymap is designed for Linux XKB Ergo-L 1.0.0 with
`compose:menu`. It keeps the number and function rows, then repurposes bottom
row keys for the layers that would normally live on split-keyboard thumb keys:

```text
LCtrl | Fn/FW | Tab/MOUSE | Esc/NAV | Space | AltGr | Enter/NUM_EDIT
      | Left Up Down Right
```

| Layer | Access | Purpose | Active-key RGB |
| --- | --- | --- | --- |
| `BASE` | Default | Positional Ergo-L typing and home-row mods | Selected RGB pattern |
| `NAV` | Hold Caps Lock or physical left Alt; tapping either sends Escape | Navigation, editing, browser actions, and Repeat | Blue |
| `NUM_EDIT` | Hold physical right Ctrl; tap sends Enter | Right-hand digits and arithmetic with left-hand editing | Green |
| `MOUSE` | Hold physical left GUI; tap sends Tab | Pointer movement, scrolling, buttons, and speed | Magenta |
| `FW` | Hold physical Fn | F1-F12, lighting, Compose, and layer locks | Yellow |

Caps Lock is therefore an additional Escape/NAV key; the bottom-row access key
is retained. Fn+H locks or unlocks `NUM_EDIT`; Fn+; does the same for `MOUSE`.
Pressing the normal access key for a locked layer also unlocks it. Arsenik
intentionally has no persistent Fn Lock because the dedicated number and
function rows make it unnecessary.

The colored Arsenik layer indicators only replace the color of keys that do
something on the active layer. Other LEDs continue showing the selected RGB
pattern. See the [complete Arsenik keymap documentation](ansi/keymaps/arsenik/readme.md)
for every layer, the Ergo-L host contract, and tap-hold timing.

## Bootloader and flashing

1. Power the laptop off and remove the keyboard input module.
2. Hold the **physical left Alt and right Alt positions** while reinstalling the
   module, then power the laptop on. The module appears as an RP2040
   mass-storage device.
3. Copy the UF2 for the intended keymap to that device.

The physical positions matter: the Arsenik keymap normally turns left Alt into
Escape/NAV, but the bootloader chord runs before QMK and is unchanged.
Bootmagic and `QK_BOOT` are intentionally unavailable. Verify that the file was
built for `framework/ansi` before copying it.

Framework's v0.3.1 release requires BIOS 4.01 or newer on the Ryzen 7040
Framework Laptop 16, or BIOS 3.00 or newer on the Ryzen AI 300 model.

## Keyboard-specific behavior

- The analog matrix adapts its press threshold when several keys in a row are
  held. The lid signal suspends the keyboard and ignores presses while the lid
  is closed, preventing accidental wake-ups in a bag.
- The dedicated Caps Lock indicator is supported independently of the RGB
  Matrix.
- The Framework factory Raw HID protocol remains available in both keymaps.
  VIA shares that interface in `default`; Arsenik keeps only the factory
  protocol so its source layout cannot be silently replaced by stored VIA data.
- The module's factory serial number is read from the final flash sector.
  Invalid or unprogrammed factory data falls back to `FRAKDKEN0100000000`.
