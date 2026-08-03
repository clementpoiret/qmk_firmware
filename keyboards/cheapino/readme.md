# Cheapino v2

QMK firmware for the [Cheapino v2](https://github.com/tompi/cheapino), a wired,
single-controller split keyboard with a 3x5+3 layout, an RP2040 controller, a
rotary encoder, and one WS2812 RGB LED.

This branch combines the Cheapino-specific matrix, encoder, and ghosting code
with a current QMK base. Its `arsenik` keymap uses positional QWERTY keycodes
translated by Linux XKB Ergo-L, eight home-row mods, the shared six-layer
architecture used by the companion ZMK Corne, function and media keys, and
mouse keys. Bluetooth controls are intentionally absent because the Cheapino
is wired.

The canonical cross-firmware layer and gesture contract lives in the companion
Corne repository's
[shared behavior specification](https://github.com/clementpoiret/zmk-corne-arsenik/blob/main/docs/shared-behavior.md).
This README documents the Cheapino implementation and hardware-specific
operations; the shared specification is authoritative if summaries differ.

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
| Enabled features | Bootmagic, extra/media keys, Mouse Keys, Repeat Key, NKRO support, encoder maps, RGB Light, and deferred execution |
| Optional diagnostic feature | QMK Console, enabled only through a build override |
| Disabled features | Caps Word in the Arsenik keymap and Command |

The keyboard supports NKRO, but `host.default.nkro` keeps the host default at
6KRO. The firmware remains NKRO-capable if a keymap later exposes its toggle.

## Arsenik keymap

The keymap is derived from OneDeadKey's original
[Arsenik project](https://github.com/OneDeadKey/arsenik). It fixes the variant
to eight home-row mods and six Selenium-style thumbs on
`LAYOUT_split_3x5_3`, without retaining inactive options for unrelated boards
or host layouts. Base keys emit QWERTY positions for Linux XKB Ergo-L;
non-base characters and shortcuts use the subset of Ergo-L 1.0.0 aliases that
the keymap actually needs.

In the diagrams below:

- `key/Layer` means tap for `key`, hold for `Layer`.
- `___` is transparent and falls through to a lower active layer.
- `x` is disabled.
- `WhL`, `WhD`, `WhU`, and `WhR` are mouse-wheel directions.

### Base layer

The primary diagram shows the semantic output produced by Linux XKB Ergo-L:

```text
 Q       C       O        P       W      | J       M        D        ODK     Y
 A/GUI   S/Alt   E/Shift  N/Ctrl  F      | L       R/Ctrl   T/Shift  I/Alt   U/GUI
 Z       X       -        V       B      | .       H        G        ,       K
             Esc/Nav  Space/Fun  Tab/Mouse | Enter/NumEdit  Backspace  RAlt
```

The firmware itself keeps the raw positional QWERTY usages shown in the shared
specification's debugging appendix.

The home-row positions become modifiers when held:

| Raw position | A | S | D | F | J | K | L | ; |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Ergo-L tap | A | S | E | N | R | T | I | U |
| Hold | Left GUI | Left Alt | Left Shift | Left Ctrl | Right Ctrl | Right Shift | Right Alt | Right GUI |

The thumb keys are:

| Position | Tap | Hold |
| --- | --- | --- |
| Left outer | Escape | NAV |
| Left home | Space | FUNCTION |
| Left inner | Tab | MOUSE |
| Right inner | Enter | NUM_EDIT |
| Right home | Backspace | - |
| Right outer | Right Alt / AltGr | - |

### Layer overview

The four work layers are available momentarily from their Base thumb. `SYSTEM`
uses a guarded two-step gesture: hold Space for `FUNCTION`, then hold the right
outer thumb. From `SYSTEM`, `NUM_EDIT` and `MOUSE` can also be toggled for
sustained work. These locks have no timeout; tap the locked layer's access
thumb to return to Base.

| # | Layer | Access | Purpose |
| --- | --- | --- | --- |
| 0 | BASE | Default | Positional QWERTY, home-row mods, and thumb tap-holds |
| 1 | NAV | Hold Escape | Navigation, browser controls, editing shortcuts, and Repeat |
| 2 | NUM_EDIT | Hold Enter, or toggle from `SYSTEM` | Digits, arithmetic, punctuation, navigation, and word editing |
| 3 | FUNCTION | Hold Space | Function keys, media, brightness, sticky modifiers, and ASCII Space |
| 4 | MOUSE | Hold Tab, or toggle from `SYSTEM` | Pointer movement, scrolling, buttons, and speed selection |
| 5 | SYSTEM | From FUNCTION, hold the right outer thumb | Bootloader, diagnostics, Caps Lock, Compose, and guarded layer toggles |

Programming symbols are provided by native Ergo-L AltGr through the plain
right-Alt thumb. `FUNCTION` provides one-shot AltGr and Shift; each remains
active for the next key or expires after one second.

Exact `NAV`, `NUM_EDIT`, `FUNCTION`, and `MOUSE` diagrams and their acceptance
criteria are maintained once in the shared behavior specification. QMK uses
Mouse Keys acceleration levels 0 and 2 for its Slow and Fast selectors; normal
mode retains QMK's accelerated default.

### SYSTEM

```text
 Bootloader Diagnostics x x x | x            x       x CapsLock Compose
 x          x           x x x | NumEditLock  x       x x MouseLock
 x          x           x x x | x            x       x x x
                    x  x  x   | x  x  x
```

`Compose` sends the Application/Menu key. On Linux XKB, configure
`compose:menu` so that key starts a Compose sequence. `NumEditLock` and
`MouseLock` toggle their layers with no idle timeout or persistent visual
indicator; use the access thumb shown on the locked layer to unlock it.
`Bootloader` is deliberately behind the two-step SYSTEM gesture. `Diagnostics`
is present only in a Console-enabled build and is disabled in the normal
release build.

## Tap-hold implementation

The shared specification owns the observable timing contract. In QMK, Flow Tap
and Chordal Hold apply only to the eight HRMs; only the four layer-tap thumbs are
marked neutral in `chordal_hold_layout`. Escape/Nav, Tab/Mouse, and
Enter/NumEdit use per-key Hold On Other Key Press, while Space/Function keeps a
more conservative Permissive Hold policy. Backspace is a plain repeatable key.

The Arsenik keymap disables QMK Caps Word because its raw keycode classification
does not follow the host-side Ergo-L translation. Use `CapsLock` on `SYSTEM`,
or one-shot Shift on `FUNCTION`, when capitalization must persist.

## Encoder behavior

Pressing the encoder sends Mute when the button is released. Rotation depends
on the active layer:

| Active layer | Counter-clockwise | Clockwise |
| --- | --- | --- |
| BASE | Volume Down | Volume Up |
| NAV | Ctrl+Shift+Tab | Ctrl+Tab |
| NUM_EDIT | Volume Down | Volume Up |
| FUNCTION | Ctrl+Z | Ctrl+Shift+Z |
| MOUSE | Wheel Down | Wheel Up |
| SYSTEM | Volume Down | Volume Up |

The encoder is connected through the custom keyboard matrix rather than QMK's
normal dedicated encoder pins. The board driver extracts only its A/B contacts,
uses a full-step quadrature state table, and sends completed detents through
QMK's normal encoder event and keymap pipelines. Layer behavior therefore lives
in `encoder_map` beside the keymap instead of depending on board-level numeric
layer IDs. The push button remains in the ordinary matrix debounce path and
generates one callback for each stable press or release.

## Matrix and ghost diagnostics

Cheapino's bidirectional, diode-free matrix needs ten historical suppression
rules. Each rule is applied to all ordered row pairs on the right half and is
mirrored six columns higher on the left half:

| Rule | Cause mask | Observed mask | Cleared phantom bit |
| --- | --- | --- | --- |
| 1 | `0x006` | `0x005` | `0x004` |
| 2 | `0x006` | `0x00A` | `0x002` |
| 3 | `0x018` | `0x014` | `0x010` |
| 4 | `0x018` | `0x028` | `0x008` |
| 5 | `0x021` | `0x011` | `0x001` |
| 6 | `0x021` | `0x022` | `0x020` |
| 7 | `0x009` | `0x00A` | `0x008` |
| 8 | `0x009` | `0x005` | `0x001` |
| 9 | `0x012` | `0x022` | `0x002` |
| 10 | `0x012` | `0x011` | `0x010` |

The firmware cannot distinguish a phantom from a legitimate switch that
produces the same complete matrix state, so these exact ambiguous patterns
retain the original suppression policy. Unit tests preserve all ten rules on
both halves and verify that unrelated bits survive. Physical chord validation
is still required on real hardware.

A Console-enabled build logs raw matrix changes, applied ghost rules, encoder
transitions, encoder-button edges, and QMK tap-hold decisions. On `SYSTEM`, tap
`Diagnostics` to toggle those logs, then run `qmk console` on the host. The
diagnostics report transitions only; they do not change the release firmware's
input policy.

## RGB behavior

The single LED defaults to a dim cyan-like color with HSV `128, 128, 32`. At
startup it performs a non-blocking 2.5-second hue sweep, then restores the color
that was active before the animation. The Arsenik keymap overlays the following
color for the highest active non-Base layer:

| Layer | LED color |
| --- | --- |
| BASE | Cyan (the configured default) |
| NAV | Blue |
| NUM_EDIT | Green |
| FUNCTION | Yellow |
| MOUSE | Magenta |
| SYSTEM | Red |

The overlay retains the configured RGB brightness and respects the RGB Light
on/off state. Momentary layers restore the previous color when released;
locked `NUM_EDIT` and `MOUSE` layers keep their color until unlocked. If
multiple layers are active, the highest layer wins, so `SYSTEM` displays red
while it is reached through `FUNCTION`.

The sweep and restoration use QMK's no-EEPROM RGB setter, so the animation does
not persist any of its intermediate frames or add flash wear at startup. RGB
lighting layers take precedence over the sweep, keeping the current layer
visible even during the startup animation.

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

For hardware troubleshooting, build the opt-in diagnostic profile and connect
QMK Console:

```sh
qmk compile -c -kb cheapino -km arsenik -e CONSOLE_ENABLE=yes
qmk console
```

The diagnostic build uses the same `cheapino_arsenik.uf2` filename as the
release build. After testing, run the normal clean-build command again before
flashing a release image.

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
- **Guarded key:** Hold Space for `FUNCTION`, hold the right outer thumb for
  `SYSTEM`, then tap the physical `Q` position.
- **Physical reset/boot controls:** Use the controller or PCB boot procedure
  documented by the hardware build if it exposes different controls.

The guarded key sends `QK_BOOT`; it is intentionally unreachable from Base in
a single press. Bootmagic, BOOTSEL, and double-tap reset remain independent
recovery paths.

## Files to edit

| Path | Purpose |
| --- | --- |
| `keyboards/cheapino/keymaps/arsenik/keymap.c` | Layers, encoder map, guarded controls, shortcuts, and tap-hold callbacks |
| `keyboards/cheapino/keymaps/arsenik/config.h` | Arsenik options and timing constants |
| `keyboards/cheapino/keymaps/arsenik/rules.mk` | Arsenik-only QMK features |
| `keyboards/cheapino/keyboard.json` | Hardware metadata, matrix pins, USB identity, and layout |
| `keyboards/cheapino/config.h` | Board-wide RGB and encoder constants |
| `keyboards/cheapino/rules.mk` | Board-wide features and custom source files |
| `keyboards/cheapino/matrix.c` | Bidirectional custom matrix scan |
| `keyboards/cheapino/ghosting.c` | Hardware-specific ghost suppression |
| `keyboards/cheapino/matrix_encoder.c` | Matrix-connected encoder driver and debounced button hook |
| `keyboards/cheapino/cheapino.c` | Board hooks and startup RGB animation |
| `tests/cheapino/test_cheapino.cpp` | Ghost-suppression and encoder regression tests |

After any keymap or configuration change, run a clean Arsenik build and inspect
the generated UF2:

```sh
qmk compile -c -kb cheapino -km arsenik
ls -l cheapino_arsenik.uf2 .build/cheapino_arsenik.uf2
```

## Remaining hardware validation

Compilation and unit tests cannot reproduce the electrical behavior of the
diode-free PCB. Before treating the input refactor as hardware-validated, use a
diagnostic build on a Cheapino v2 to check:

1. One clockwise and counter-clockwise event per detent at slow and fast speeds.
2. One Mute action per encoder-button release, including noisy presses.
3. Nearby key chords while rotating or pressing the encoder.
4. Each logged ghost-rule activation against the intended physical chord, plus
   legitimate chords that share rows or columns with the ten masks.

Speculative Hold, dynamic tap-hold calibration, and Mouse Keys tuning remain
separate usability experiments; they are not part of this hardware refactor.

## Troubleshooting

- **No UF2 appears after compilation:** Check both the repository root and
  `.build/`. The expected file is `cheapino_arsenik.uf2`.
- **The UF2 drive never appears:** Retry Bootmagic with the physical `Y` key or
  use the controller's BOOTSEL procedure. Run `qmk doctor` for host-side setup
  problems.
- **The wrong layout appears after flashing:** Confirm that the copied file is
  `cheapino_arsenik.uf2`, not `cheapino_default.uf2`.
- **ODK typography does not work:** Confirm the host is using Linux XKB Ergo-L;
  the firmware now sends Ergo-L's native one-dead-key sequence rather than QMK
  Unicode input.
- **Saved lighting settings disappeared:** Bootmagic intentionally clears
  EEPROM.
- **Mouse movement feels too fast or uneven:** The current firmware uses QMK's
  default Mouse Keys settings; see the Mouse Keys enhancement above.

For general QMK information, see the
[build guide](https://docs.qmk.fm/newbs_building_firmware),
[RP2040 flashing guide](https://docs.qmk.fm/flashing#raspberry-pi-rp2040-uf2),
and [QMK keycode reference](https://docs.qmk.fm/keycodes).
