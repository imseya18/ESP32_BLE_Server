# ESP32\_BLE\_Server

## Description

ESP32\_BLE\_Server is a Bluetooth Low Energy (BLE) server for the ESP32-S3 that allows controlling a WS2812B LED strip via a custom binary payload.

The project uses:

* **NimBLE-Arduino** for the BLE stack
* **FastLED** for driving the WS2812B LEDs

A client application (e.g., Tauri, nRF Connect, or any BLE-enabled app) can send a binary buffer to change color, adjust brightness, or trigger effects on the strip.

## Prerequisites

* **PlatformIO** installed ([https://platformio.org/](https://platformio.org/))
* **ESP32-S3 DevKitC-1** or equivalent
* WS2812B LED strip (60 LEDs)

## Installation

1. Clone the repository:

   ```bash
   git clone git@gitlab.com:witekio/rnd/b0000-witekio-welma/test-bench-vizualizer/esp32-ble-server.gitgithub.com/imseya18/ESP32_BLE_Server.git
   cd ESP32_BLE_Server
   ```
2. Open the project in VS Code + PlatformIO, or build from the command line:

   ```bash
   pio run
   ```
3. Flash the firmware to your board:

   ```bash
   pio run --target upload
   ```
4. Open the serial monitor at 115200 baud:

   ```bash
   pio device monitor
   ```

## Wokwi Simulation

The project includes `diagram.json` and `wokwi.toml` to visualize the ESP32-S3 and a 60-LED canvas in Wokwi:
**wokwi** vsCode extension **needed**

## BLE GATT Profile

* **Service UUID**: `d0d02988-9d8c-41e1-abbc-c1587419475d` (LED Strip)
* **Characteristic UUID**: `b18d531d-0d2e-4315-b253-677c0b9bdf72` (ColorBuffer)

  * Properties: `WRITE_NR`
  * Length: 7 bytes

## Payload Protocol

| Byte Index | Meaning                                  |
| ---------- | ---------------------------------------- |
| 0          | `START_FLAG` (0x38)                      |
| 1          | `SEGMENT_ID` (0–14)                      |
| 2          | Red component (0–255)                    |
| 3          | Green component (0–255)                  |
| 4          | Blue component (0–255)                   |
| 5          | `COMMAND` (0x01=color, 0x02=brightness…) |
| 6          | `END_FLAG` (0x83)                        |
