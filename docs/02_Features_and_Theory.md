# Features and Theory

The smart greenhouse provides four primary autonomous features designed to mimic a natural self-sustaining environment.

## 1. Automated Irrigation

Irrigation represents the core critical function of a greenhouse. The system continuously polls an analog soil moisture sensor placed deep within the plant substrate.
By averaging 100 consecutive analog readings to mitigate random noise spikes, the Arduino derives a reliable moisture score ranging from 0 (heavily saturated) to values exceeding 400 (very dry).
When the averaged value breaches the defined `MOISTURE_THRESHOLD` (set at 400), the logic triggers a digital output. This activates a heavy-duty relay running on an isolated 9V circuit, powering a submerged DC water pump until the measured soil saturation satisfies the established target, resulting in continuous hands-free watering.

## 2. Climate Monitoring and Window Ventilation

Ambient climatic shifts can stress plants quickly, so internal temperature, humidity, and barometric pressure are gathered via high-precision I2C communications utilizing a BME280 sensor breakout.
To prevent the rapid toggling of the greenhouse window (a continuous open-close loop known as "chattering" that could burn out the servo motor), the software incorporates **hysteresis** logic.
- Variables like `max_temp`, `min_temp`, `max_hum`, and `min_hum` are defined with additional variable margins (`temp_margin`, `hum_margin`). 
- If the temperature crosses above the maximum plus the margin, the servo motor mechanically drives the acrylic roof window open (`window_open_pos` set to 90 degrees) to allow external air circulation.
- Conversely, the window will not close again until the conditions drop below the minimum boundary minus its respective margin (`window_close_pos` set to 180 degrees), ensuring smooth and intentional ventilation cycles without motor fatigue.

## 3. Reactive Lighting Simulation

Natural sunlight cycles form the basis of photosynthesis. The module employs a digital photodiode detector calibrated via a physical potentiometer to identify a specific darkness threshold. When sunset occurs or artificial lighting drops to absolute zero, the Arduino identifies the `HIGH` digital state.
The MCU reacts by initializing a hardware PWM (Pulse Width Modulated) looping function. Rather than merely turning on the RGB LED starkly, it uses a non-blocking mathematical conversion loop (`hsvToRgb`). This loop slowly advances the hue angle over a timeframe of fractional milliseconds, continuously calculating RGB values while applying Gamma Correction, ensuring a smooth visual transition across the light spectrum to supplement the plant's light diet aesthetically.

## 4. Diagnostics Display

While automation negates the need for manual check-ups, monitoring system health is critical. To this end, an organic light-emitting diode (OLED) panel interfaces directly alongside the BME280 over the same two-wire interface (I2C) using the address `0x3C`.
Every 3000 milliseconds, the loop pushes an updated hardware snapshot to the 128x32 screen buffer—alternating automatically between displaying the latest temperature/humidity readings and the real-time digitized soil/light variables.