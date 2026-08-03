# Framework Laptop 16 ANSI keyboard

Firmware for the standard 78-key ANSI Framework Laptop 16 keyboard input module (right Ctrl, USB VID `0x32AC`, PID `0x0012`). This is a forward-port of Framework's v0.3.1 firmware to the QMK version in this repository.

- Maintainer: [Daniel Schaefer](https://github.com/JohnAZoidberg)
- Hardware: [Framework Laptop 16 keyboard](https://frame.work/products/laptop16-diy-amd-7040)
- Vendor source: [Framework QMK v0.3.1](https://github.com/FrameworkComputer/qmk_firmware/tree/v0.3.1/keyboards/framework)

This target is not compatible with the Copilot, ISO, JIS, numpad, or macropad input modules.

## Build

```sh
qmk compile -kb framework/ansi -km default
```

The deployable image is written to `.build/framework_ansi_default.uf2` and copied to the repository root.

## Bootloader and flashing

1. Power the laptop off and remove the keyboard input module.
2. Hold left Alt and right Alt while reinstalling the module, then power the laptop on. The module appears as an RP2040 mass-storage device.
3. Copy `framework_ansi_default.uf2` to that device.

Bootmagic is intentionally disabled because the module uses its hardware Alt-key bootloader chord. Flashing is a manual operation; verify that the UF2 was built for `framework/ansi` before copying it.

Framework's v0.3.1 release requires BIOS 4.01 or newer on the Ryzen 7040 Framework Laptop 16, or BIOS 3.00 or newer on the Ryzen AI 300 model.

## Default behavior

The default keymap provides the released media-key top row, an Fn layer with F1–F12 and lighting controls, persistent Fn lock, VIA remapping with ten dynamic layers, RGB and white-backlight controls, display switching, and the airplane-mode HID key.

The firmware reads the module's factory serial number from the final flash sector. Invalid or unprogrammed factory data falls back to `FRAKDKEN0100000000`.
