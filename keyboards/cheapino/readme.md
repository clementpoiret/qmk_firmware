# Cheapino v2

QMK firmware for the [Cheapino v2](https://github.com/tompi/cheapino), a wired,
single-controller split keyboard with a 3x5+3 layout, an RP2040 controller, a
rotary encoder, and one WS2812 RGB LED.

This branch combines the Cheapino-specific matrix, encoder, and ghosting code
with a current QMK base. Its `arsenik` keymap closely follows the Arsenik
Selenium configuration used by the companion ZMK Corne: QWERTY, home-row mods,
four thumb tap-holds, navigation, numbers, symbols, function keys, media keys,
mouse keys, and Linux Unicode input. Bluetooth controls are intentionally absent
because the Cheapino is wired.

Unlike the two-controller ZMK Corne, the Cheapino uses one RP2040 for the whole
keyboard. Build and flash **one UF2 file**, not separate left and right images.

## Hardware and firmware

| Item | Current configuration |
| --- | --- |
| Physical layout | Split 3x5+3, 36 keys |
| Controller | RP2040 |
| Bootloader | RP2040 UF2 |
| QMK keyboard target | `cheapino` |
| Main keymap | `arsenik` |
| Community layout | `split_3x5_3` |
| Encoder | Matrix-connected rotary encoder with push button |
| Lighting | One WS2812 RGB LED on `GP16` |
| Matrix | Custom bidirectional scanner with Cheapino-specific ghost suppression |
| USB identity | VID `0xFEE3`, PID `0x10B8`, device version `1.0.1` |
| Enabled features | Bootmagic, Caps Word, extra/media keys, Mouse Keys, NKRO support, RGB Light, deferred execution, and Unicode |
| Disabled features | Command and Console |

The keyboard supports NKRO, but does not request NKRO as the host default. The
current metadata still expresses that with the obsolete
`"usb.force_nkro": false` field; replacing it with the current host-default
metadata is listed in [Potential enhancements](#potential-enhancements).

## Arsenik keymap

The keymap is derived from OneDeadKey's original
[Arsenik project](https://github.com/OneDeadKey/arsenik). The active
configuration is its Selenium variant for `LAYOUT_split_3x5_3`, using a QWERTY
host layout and Linux Unicode input.

In the diagrams below:

- `key/Layer` means tap for `key`, hold for `Layer`.
- `___` is transparent and falls through to a lower active layer.
- `x` is disabled.
- `WhL`, `WhD`, `WhU`, and `WhR` are mouse-wheel directions.

### Base layer

```text
 Q       W       E        R       T      | Y       U        I        O       P
 A/GUI   S/Alt   D/Shift  F/Ctrl  G      | H       J/Ctrl   K/Shift  L/Alt   ;/GUI
 Z       X       C        V       B      | N       M        ,        .       /
             Esc/Vim  Space/Fun  Tab/Mouse | Enter/NumNav  Backspace  RAlt
```

The home-row keys become modifiers when held:

| Tap | A | S | D | F | J | K | L | ; |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Hold | Left GUI | Left Alt | Left Shift | Left Ctrl | Right Ctrl | Right Shift | Right Alt | Right GUI |

The thumb keys are:

| Position | Tap | Hold |
| --- | --- | --- |
| Left outer | Escape | Vim navigation |
| Left home | Space | Function pad |
| Left inner | Tab | Mouse pad |
| Right inner | Enter | Number navigation |
| Right home | Backspace | - |
| Right outer | Right Alt / AltGr | - |

### Layer overview

Layers are momentary. Hold their access key, use the layer, and release it to
return. Lafayette and Number Row are reached through a thumb-key transfer: enter
Function, hold a `LAF` thumb, then release the Function thumb while keeping
`LAF` held. Number Row is reached similarly from Lafayette with a `NUM` thumb.

| # | Layer | Access | Purpose |
| --- | --- | --- | --- |
| 0 | Base | Default | QWERTY, home-row mods, and thumb tap-holds |
| 1 | Lafayette | From Function, hold either outer `LAF` thumb | Programming symbols |
| 2 | Number Row | From Lafayette, hold either outer `NUM` thumb | Shifted symbols, numbers, and Unicode punctuation |
| 3 | Vim Navigation | Hold the Escape thumb | Navigation, browser controls, editing shortcuts, and scrolling |
| 4 | Number Navigation | Hold the Enter thumb, or use `NumNav` from Vim Navigation | Numpad plus left-hand navigation and editing shortcuts |
| 5 | Function Pad | Hold the Space thumb | Function keys, media, brightness, and explicit modifiers |
| 6 | Mouse Pad | Hold the Tab thumb | Pointer movement, scrolling, and mouse buttons |

### Lafayette symbols

```text
 ^       <       >       $       %      | @       &       *       '       `
 {       (       )       }       =      | \\      +       -       /       "
 ~       [       ]       _       #      | PIPE    !       ;       :       ?
                  NUM  Space  ___        | ___  Backspace  NUM
```

### Number Row

```text
 !       @       #       $       %      | ^       &       *       (       )
 1       2       3       4       5      | 6       7       8       9       0
 „       “       ”       ¢       ‰      | x       -       ,       .       /
                  LAF  Space  ___        | ___  Backspace  LAF
```

The five non-ASCII characters use QMK's Linux Unicode input mode. The host must
support the Linux `Ctrl+Shift+U` input sequence.

### Vim Navigation

```text
 NumNav  Ctrl+T  BrowserBack  BrowserFwd  x   | Home  PgDn  PgUp  End    GUI+P
 Ctrl+A  Ctrl+S  Shift+Tab    Tab         x   | Left  Down  Up    Right  Fun
 Ctrl+Z  Ctrl+X  Ctrl+C       Ctrl+V      x   | WhL   WhD   WhU   WhR    x
                         ___  ___  ___         | ___  Delete  Escape
```

### Number Navigation

```text
 Tab     Home    Up      End     PgUp       | /   7   8   9   GUI+P
 Ctrl+A  Left    Down    Right   PgDn       | -   4   5   6   0
 Ctrl+Z  Ctrl+X  Ctrl+C  Ctrl+V  Shift+Tab  | ,   1   2   3   .
                         ___  ___  ___       | ___  Delete  Escape
```

### Function Pad

```text
 F1  F2   F3   F4   x   | PrintScreen  Brightness-  Brightness+  Vol-/Mute  Vol+
 F5  F6   F7   F8   x   | x            LeftCtrl     LeftShift    LeftAlt    LeftGUI
 F9  F10  F11  F12  x   | x            Previous     Play/Pause   Next       x
                    LAF  Space  ___      | ___  Backspace  LAF
```

`Vol-/Mute` sends Volume Down when tapped and Mute when held.

### Mouse Pad

```text
 x  x  x  x  x   | x     Button1  Button3  Button2  x
 x  x  x  x  x   | Left  Down     Up       Right    x
 x  x  x  x  x   | WhL   WhD      WhU      WhR      x
             Delete  ___  ___      | ___  ___  Escape
```

Mouse Keys currently use QMK's accelerated defaults. No keymap-specific speed,
interval, or wheel tuning is applied yet.

## Tap-hold behavior

The timing and decision policy intentionally mirrors the ZMK keyboard as
closely as the two firmware implementations allow:

| Setting | Current value or behavior |
| --- | --- |
| Home-row mod tapping term | 200 ms |
| Thumb layer-tap tapping term | 150 ms |
| `Vol-/Mute` tapping term | 200 ms |
| Home-row quick-tap term | 175 ms |
| Other quick-tap term | 0 ms |
| Flow Tap | 150 ms after every preceding key |
| Chordal Hold | Same-hand rolls prefer taps; opposite-hand chords may hold |
| Permissive Hold | Enabled per key, except for `Vol-/Mute` |

The custom `get_flow_tap_term()` deliberately applies the 150 ms Flow Tap term
to every preceding key. This is broader than QMK's guarded default and matches
ZMK's `require-prior-idle-ms = <150>` behavior more closely. It should remain
unchanged unless real use shows missed layer holds after navigation, media, or
shortcut keys.

Caps Word is compiled and configured for activation with both Shift modifiers.
On this 3x5 map, Shift is provided by holding the `D` and `K` home-row mod-taps;
there is no dedicated Caps Word key.

## Encoder behavior

Pressing the encoder sends Mute when the button is released. Rotation depends
on the active layer:

| Active layer | Counter-clockwise | Clockwise |
| --- | --- | --- |
| Vim Navigation | Ctrl+Shift+Tab | Ctrl+Tab |
| Function Pad | GUI+Z | GUI+Y |
| Base and all other layers | Volume Down | Volume Up |

The encoder is connected through the custom keyboard matrix rather than QMK's
normal dedicated encoder pins. Its current implementation reads raw matrix
state before QMK's debounce stage and embeds the Arsenik layer numbers in
keyboard-level code. The proposed test and refactor work is described under
[Potential enhancements](#potential-enhancements).

## RGB behavior

The single LED defaults to a dim cyan-like color with HSV `128, 128, 32`. At
startup it performs a non-blocking 2.5-second hue sweep, then restores the color
that was active before the animation. Layer colors are intentionally disabled;
an earlier implementation was found distracting.

The current animation uses the EEPROM-writing RGB setter for every frame. That
does not affect the intended appearance, but it causes unnecessary persistent
writes and is the first item in the enhancement backlog.

## Set up the build environment

Install the QMK CLI and platform dependencies by following the official
[QMK environment setup guide](https://docs.qmk.fm/newbs_getting_started).

For a fresh checkout of this fork and branch:

```sh
qmk setup clementpoiret/qmk_firmware -b cheapinov2
```

The command prints the QMK home directory it created. Change to that directory,
then verify the toolchain:

```sh
cd /path/to/qmk_firmware
qmk doctor
```

If this repository is already cloned, make sure the QMK CLI points at this
checkout rather than another QMK installation:

```sh
qmk setup -H /absolute/path/to/qmk_firmware
qmk doctor
```

## Compile

From the root of this repository, compile the Arsenik firmware with:

```sh
qmk compile -kb cheapino -km arsenik
```

The equivalent Make command is:

```sh
make cheapino:arsenik
```

A successful build creates the same UF2 in two useful locations:

```text
cheapino_arsenik.uf2
.build/cheapino_arsenik.uf2
```

The copy in the repository root is the easiest one to flash. If it is missing,
confirm that the command completed successfully and that it was run from the
QMK repository containing `keyboards/cheapino`.

To force a clean rebuild:

```sh
qmk compile -c -kb cheapino -km arsenik
```

The legacy/default keymap can still be built separately:

```sh
qmk compile -kb cheapino -km default
```

That command produces `cheapino_default.uf2`; it is not the Arsenik layout
documented above.

## Install the firmware

### Manual UF2 installation

1. Compile `cheapino_arsenik.uf2`.
2. Put the RP2040 into its UF2 bootloader using one of the methods in
   [Bootloader and recovery](#bootloader-and-recovery).
3. Wait for the controller to appear as a removable USB drive, commonly named
   `RPI-RP2`.
4. Copy `cheapino_arsenik.uf2` to that drive using a file manager or `cp`.
5. Wait for the drive to disconnect and the keyboard to restart.

Only one controller and one UF2 are involved. Do not look for separate left and
right images.

### QMK CLI installation

QMK can build and wait for the bootloader in one command:

```sh
qmk flash -kb cheapino -km arsenik
```

Enter the bootloader when prompted. For RP2040 boards, manually copying the UF2
is often simpler and does not require a dedicated flashing application.

## Bootloader and recovery

Use any available method:

- **Bootmagic:** Unplug the keyboard, hold the physical `Y` key, reconnect USB,
  and release the key after the UF2 drive appears. The default matrix position
  is `[0,0]`, which is `Y` on Cheapino's irregular matrix, not the physical
  top-left `Q` key. Bootmagic resets EEPROM, including saved RGB settings.
- **BOOTSEL:** Hold the RP2040 controller's `BOOTSEL` button while connecting
  USB, if the button is accessible.
- **Double-tap reset:** Quickly press the controller's reset control twice. The
  selected `GENERIC_PROMICRO_RP2040` platform enables QMK's 200 ms double-tap
  bootloader window.
- **Physical reset/boot controls:** Use the controller or PCB boot procedure
  documented by the hardware build if it exposes different controls.

The Arsenik keymap does not currently map `QK_BOOT`. Bootmagic, BOOTSEL, and
double-tap reset remain available without a keymap-level boot key.

## Files to edit

| Path | Purpose |
| --- | --- |
| `keyboards/cheapino/keymaps/arsenik/keymap.c` | Layers, encoder-related layer names, shortcuts, and tap-hold callbacks |
| `keyboards/cheapino/keymaps/arsenik/config.h` | Arsenik options and timing constants |
| `keyboards/cheapino/keymaps/arsenik/rules.mk` | Arsenik-only QMK features |
| `keyboards/cheapino/keyboard.json` | Hardware metadata, matrix pins, USB identity, and layout |
| `keyboards/cheapino/config.h` | Board-wide RGB, Caps Word, and timing defaults |
| `keyboards/cheapino/rules.mk` | Board-wide features and custom source files |
| `keyboards/cheapino/matrix.c` | Bidirectional custom matrix scan |
| `keyboards/cheapino/ghosting.c` | Hardware-specific ghost suppression |
| `keyboards/cheapino/encoder.c` | Matrix-connected encoder decoding and actions |
| `keyboards/cheapino/cheapino.c` | Startup RGB animation |

After any keymap or configuration change, run a clean Arsenik build and inspect
the generated UF2:

```sh
qmk compile -c -kb cheapino -km arsenik
ls -l cheapino_arsenik.uf2 .build/cheapino_arsenik.uf2
```

## Potential enhancements

The items below are proposals discovered while reviewing the current QMK
features and Cheapino implementation. **They are not implemented yet.** Changes
that affect input timing or the encoder require physical keyboard testing in
addition to successful compilation.

| Priority | Enhancement | Proposed outcome | Effort / change risk |
| --- | --- | --- | --- |
| 1 | Stop the RGB animation from persisting every frame | Use `rgblight_sethsv_noeeprom()` during the sweep and restoration, avoiding roughly 51 logical EEPROM writes per boot | Small / low |
| 2 | Trial constrained Speculative Hold | Apply Shift/Ctrl immediately for responsive Shift+click and Ctrl+scroll, while retaining the current tap-hold decisions | Small / medium |
| 3 | Test and modernize the encoder path | Characterize current behavior, debounce the button and quadrature transitions, and move layer actions out of hard-coded keyboard-level layer numbers | Medium / medium |
| 4 | Calibrate tap-hold timings dynamically | Use a temporary Dynamic Tapping Term build to measure QMK-specific HRM and thumb timings, then bake in the chosen constants and remove the controls | Small / low |
| 5 | Add Repeat and Alternate Repeat | Use two currently disabled Vim-layer positions for `QK_REP` and `QK_AREP`, including QMK's built-in reverse navigation, mouse, browser, media, and editing pairs | Small / low |
| 6 | Add Layer Lock with an idle timeout | Allow sustained navigation or mouse work without holding a thumb key; automatically unlock after 30-60 seconds | Small / medium |
| 7 | Tune Mouse Keys | Trial a 16 ms movement interval for a 60 Hz display and reduce maximum speed proportionally; keep accelerated mode unless another mode proves better in use | Small / low-medium |
| 8 | Preserve or selectively guard Flow Tap | Keep the current unconditional 150 ms behavior for ZMK parity; only adopt QMK's alpha/Space and hotkey guards if missed layer holds are observed | Small / medium behavior change |
| 9 | Migrate the NKRO default metadata | Remove obsolete `usb.force_nkro`; express `host.default.nkro: false` with current QMK metadata, and do not enable default-on NKRO without a demonstrated greater-than-6-key chord | Small / low |

### Speculative Hold trial

The initial experiment should be limited to QMK's default Shift/Ctrl mod-taps
and use the safeguards added by current QMK:

```c
#define SPECULATIVE_HOLD
#define SPECULATIVE_HOLD_ONE_KEY
#define SPECULATIVE_HOLD_FLOW_TERM 150
```

This is most relevant to the `D`, `F`, `J`, and `K` home-row mods when combined
with mouse buttons or wheel keys. The trial must check for "flashing mods,"
where an application reacts to a modifier press and release that was ultimately
resolved as a tap.

### Encoder dependency order

Characterization tests must land before the encoder refactor. They should cover
clockwise and counter-clockwise transitions, bounce, skipped transitions,
button press/release bounce, every layer action, all ghost-suppression patterns,
and nearby legitimate key chords. After that baseline exists, the hardware code
can expose a keymap-level hook so Arsenik uses named layers instead of the raw
numbers `3`, `5`, and `6`.

### Timing calibration

Dynamic Tapping Term should be a temporary diagnostic build, not permanent UI.
Place `DT_UP`, `DT_DOWN`, and `DT_PRNT` in unused positions, make the per-key
callback honor `g_tapping_term`, test real typing and layer entry, record the
selected HRM/thumb values, then remove the diagnostic feature.

### Mouse Keys and layer features

Repeat/Alternate Repeat and Layer Lock both fit currently disabled positions on
Vim Navigation or Mouse Pad. Layer Lock should include an idle timeout because
the keyboard has no persistent display or layer-color indication. Mouse tuning
is subjective: compare the current 20 ms accelerated default against a 16 ms
interval on the actual host, while lowering `MOUSEKEY_MAX_SPEED` enough to keep
the same usable range.

### Recommended implementation order

1. Fix the RGB animation's persistent writes.
2. Add characterization tests, then refactor the encoder.
3. Independently trial constrained Speculative Hold.
4. Use a temporary build to calibrate tap-hold timings.
5. Choose key positions for Repeat/Alternate Repeat and Layer Lock.
6. Tune Mouse Keys on the physical keyboard.
7. Preserve Flow Tap unless testing proves that its broad ZMK-compatible policy
   causes missed holds.
8. Migrate the obsolete NKRO metadata without turning NKRO on by default.

## Troubleshooting

- **No UF2 appears after compilation:** Check both the repository root and
  `.build/`. The expected file is `cheapino_arsenik.uf2`.
- **The UF2 drive never appears:** Retry Bootmagic with the physical `Y` key or
  use the controller's BOOTSEL procedure. Run `qmk doctor` for host-side setup
  problems.
- **The wrong layout appears after flashing:** Confirm that the copied file is
  `cheapino_arsenik.uf2`, not `cheapino_default.uf2`.
- **Unicode punctuation does not work:** The keymap selects Linux Unicode mode;
  other operating systems require a different `UNICODE_SELECTED_MODES` value.
- **Saved lighting settings disappeared:** Bootmagic intentionally clears
  EEPROM.
- **Mouse movement feels too fast or uneven:** The current firmware uses QMK's
  default Mouse Keys settings; see the Mouse Keys enhancement above.

For general QMK information, see the
[build guide](https://docs.qmk.fm/newbs_building_firmware),
[RP2040 flashing guide](https://docs.qmk.fm/flashing#raspberry-pi-rp2040-uf2),
and [QMK keycode reference](https://docs.qmk.fm/keycodes).
