# Software Architecture

The software logic orchestrates the `greenhouse.ino` source code sequentially over hardware loops inside the Arduino IDE, primarily utilizing non-blocking polling mechanics instead of standard delays.

## Dependencies

The source relies on universally standard libraries initialized over `SPI.h` and `Wire.h`:
- `Adafruit_GFX.h` / `Adafruit_SSD1306.h` for drawing characters, allocating memory strings, and hardware scrolling onto the tiny OLED screen block.
- `Adafruit_BME280.h` / `Adafruit_Sensor.h` for environmental value interpolation over precise I2C data packets.
- `Servo.h` to transmit mapped pulse-width signals (`0-180`) into physical mechanical motion on the structural hinges.

## System Logic

Inside `loop()`, the software avoids `delay()` commands because stopping execution prevents time-critical processes—such as LED fading (`discoStep()`) and immediate sensor polling—from achieving synchronization.

### Sensor Cycles
Instead of waiting out an interval natively, the `sensors` rely on an `unsigned long SENSOR_INTERVAL_MS = 1000;`. Every calculated second, the program measures the real-time threshold and immediately determines output logic.

- If `temp > max_temp - temp_margin`, `window_angle = window_open_pos;`, enforcing safety against "chattering" or bouncing conditions via hysteresis margins (`temp_margin = 2`).
- A `measureandpour()` handler reads `soil_moisture_pin` 100 consecutive times into a `long` array. The average output mitigates random voltage spikes. If this consolidated `soil` reading exceeds `MOISTURE_THRESHOLD` (400), it energizes `digitalWrite(rele_pin, LOW)` and pulls the pump contacts together.

### Aesthetics and Color Space
When the sensor on `D2` outputs `HIGH`, a state machine toggles `discoEnabled = true`. The program then iterates every `10` milliseconds, running the `discoStep()` sequence mathematically, continuously converting `hsvToRgb` from Hue 0.0f to 1.0f on a fractional loop. Additionally, the RGB output integers interface with a non-linear `gammaCorrect(int value)` multiplier (applying a mathematical power of 2.2), ensuring smooth human-eye transition capabilities for lower-cost diodes.