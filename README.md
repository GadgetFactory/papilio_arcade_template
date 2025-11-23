# papilio_arcade_template

This repository contains an example FPGA + ESP32 project for the Papilio Arcade board.

What's included:
- Gateware (Verilog) under `src/gateware/` and the `wishbone/` library.
- An Arduino example sketch `src/esp32_rgb_led_example.ino` that uses the `lib/wishbone_spi` helper.

Usage:
- Open `papilio_arcade_template.code-workspace` in VS Code to load the workspace with the new project name.
- Build FPGA: use the VS Code task "FPGA: Build (TCL)" (configured in the workspace tasks).
- Build ESP32 sketch with PlatformIO as usual.
