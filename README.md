# Greenhouse Hexaplant

![Assembled Greenhouse](docs/images/Greenhouse-assembled.jpg)

A smart greenhouse prototype developed as part of the **Erasmus 2026** exchange program between German and Spanish students. The system uses an Arduino Nano to automate plant care by monitoring environmental conditions and responding in real time.

---

## Table of Contents

- [Overview](#overview)
- [Extended Documentation](#extended-documentation)
- [Features](#features)
- [Bill of Materials](#bill-of-materials)
- [Wiring](#wiring)
  - [Pin Mapping](#pin-mapping)
  - [Motor Circuit](#motor-circuit)
- [Assembly](#assembly)
  - [3D Printing](#3d-printing)
  - [Laser Cutting](#laser-cutting)
- [Software](#software)
  - [Dependencies](#dependencies)
  - [Project Structure](#project-structure)
- [Flashing](#flashing)
- [How It Works](#how-it-works)
- [Credits](#credits)
- [License](#license)

---

## Overview

The greenhouse monitors soil moisture, ambient light, temperature, humidity, and barometric pressure. Based on sensor readings it can:

- **Water plants automatically** when the soil is too dry.
- **Open a window** via servo motor when humidity is too high.
- **Activate RGB lighting** when it gets dark.
- **Display sensor data** on a built-in OLED screen.

The enclosure is designed to be assembled from 3D-printed and laser-cut parts so it can be transported easily (e.g. on an airplane).

---

## Extended Documentation

For a detailed, professional breakdown of the project's engineering, collaboration, and specific mechanisms, please consult the extended documentation files in the `docs` folder:

* [01 Project Overview](docs/01_Project_Overview.md)
* [02 Features and Theory](docs/02_Features_and_Theory.md)
* [03 Components and Hardware](docs/03_Components_and_Hardware.md)
* [04 Planning and Collaboration](docs/04_Planning_and_Collaboration.md)
* [05 Software Architecture](docs/05_Software_Architecture.md)
* [06 Difficulties and Conclusions](docs/06_Difficulties_and_Conclusions.md)
* [07 Future Improvements](docs/07_Future_Improvements.md)

You can also browse the [Main Directory Documentation Index](docs/README.md) for a summary of these topics, or view the [Source Code (`greenhouse.ino`)](greenhouse.ino) directly.

---

## Features

| Feature | Description |
|---|---|
| Automatic irrigation | A soil moisture sensor triggers a relay-driven water pump when the soil drops below a configurable threshold. |
| Light detection | A photodiode detects darkness and activates an RGB LED with a smooth color-fading effect. |
| Climate monitoring | A BME280 sensor measures temperature, humidity, and barometric pressure. |
| OLED display | A 128×32 I²C OLED shows live sensor readings. |
| Window control | A servo motor opens and closes a greenhouse window based on environmental conditions. |

---

## Bill of Materials

| # | Component | Quantity | Notes |
|---|---|---|---|
| 1 | Arduino Nano (Rev 3.0) | 1 | ATmega328P, CH340 USB |
| 2 | BME280 Breakout | 1 | Temperature, humidity, barometric pressure (I²C) |
| 3 | OLED Display 128×32 | 1 | SSD1306, I²C address `0x3C` |
| 4 | Capacitive Soil Moisture Sensor | 1 | Analog output |
| 5 | KY-019 5V Relay Module | 1 | Controls the water pump |
| 6 | DC Water Pump | 1 | Driven via relay |
| 7 | Servo Motor (9g) | 1 | Window control |
| 8 | Photodiode Module | 1 | Digital output (dark/light) — TCRT5000 footprint¹ |
| 9 | RGB LED (common cathode) | 1 | |
| 10 | 220Ω Resistor | 3 | One per RGB channel |
| 11 | 9V Battery Pack | 2 | One for Arduino (VIN), one for motor circuit |
| 12 | Irrigation hose + fittings | 1 set | Included with pump kit |

> ¹ The TCRT5000 is used as a placeholder in the schematic. The actual module is a photodiode breakout with four pins: **VCC**, **GND**, **DO** (digital out), **AO** (analog out).

---

## Wiring

![Wiring Schematic](docs/schematic.png)

### Pin Mapping

| Arduino Pin | Component | Component Pin |
|---|---|---|
| `D2` | Photodiode module | DO (digital out) |
| `D3` | Servo motor | Signal (pulse) |
| `D9` | 220Ω → RGB LED | Red anode |
| `D5` | 220Ω → RGB LED | Blue anode |
| `D6` | 220Ω → RGB LED | Green anode |
| `D7` | Relay module (KY-019) | S (signal) |
| `A4` | BME280 / OLED display | SDA |
| `A5` | BME280 / OLED display | SCL |
| `A6` | Soil moisture sensor | SIG |
| `5V` | Display, photodiode, soil sensor, relay, servo | VCC |
| `3V3` | BME280 | 3.3V |
| `GND` | All components | GND |
| `VIN` | 9V battery #1 | + |

### Motor Circuit

The water pump runs on a **separate 9V power supply** switched through the relay:

| From | To |
|---|---|
| 9V Battery #2 (+) | Relay COM |
| Relay NO | DC Motor pin 1 |
| DC Motor pin 2 | 9V Battery #2 (−) |
| 9V Battery #2 (−) | Common GND |

> The relay isolates the motor circuit from the Arduino's logic power, preventing voltage spikes from damaging the microcontroller.

---


## Assembly

### 3D Printing

Structural parts of the greenhouse are provided as **STL** files in the [`3D/`](3D/) directory. Print with standard PLA or PETG at 0.2 mm layer height.

### Laser Cutting

Panel and wall templates are provided as **SVG** files in the [`laser/`](laser/) directory. Designed for acrylic (Plexiglas) sheets.

> The greenhouse is designed with snap-fit / plug-in connections so it can be assembled and disassembled without tools for easy transport.

### Step By Step

1. Printing
  Print all needed Parts from [3D Printing](#3d-printing). You can also print the water tank extension but you can just take a bottle or cub.

2. Wiring
  Assemble the 3D Printed structure of the Greenhouse so you know where to put the sensors and the actors.

  Allways have a look on the wiring mentioned in [Wiring](#wiring). You need to connect the stuff to the arduino exactly like in our plan.
  
  The RGB LEDs needs to be in the plant tank and point to the plant.
  
  The servo needs to be glued on the Pillar Top, so it can open the Window with rotation. To get a longer arm we used [a model from Makerworld](https://makerworld.com/de/models/981832-servo-arms-horn-and-hook) (the 40mm one).

  The pump can be put into the tank extension or just into a water bottle. The pipe can be threaded through one of the holes provided in the Plant Base or Pillar Top.

  The sensors also needs to be put inside the plant tank. Just glue them where is practicable. Use the holes for wiring.

3. Code
  Flash the code found in [Flashing](#flashing). Please check if the servo is spining in the right direction. Please check if the variables are fitting your needs.

4. Glass
  You need a laser cutter for the glass and cut it like mentioned in [Laser Cutting](#laser-cutting).

3. Assemble
  Now you need to put the glass into the rails in the pillars to rotate them correctly. Then glue the Pillars to the bottom.
  On the top you need the two windows to glue on the Top Window Holder. The first gets glued completely onto one side. The second needs to be on the side with the slight dip. You only glue the second with a hinge into the slight dip.

  Put the Plant Base tight onto the Base and the Window can be put onto the Pillar Top and It can be easily lifted and removed.

---

## Software

### Dependencies

| Library | Source | Notes |
|---|---|---|
| **Adafruit GFX Library** | [GitHub](https://github.com/adafruit/Adafruit-GFX-Library) | Core graphics library for the display |
| **Adafruit SSD1306** | [GitHub](https://github.com/adafruit/Adafruit_SSD1306) | OLED driver |
| **Adafruit BusIO** | [GitHub](https://github.com/adafruit/Adafruit_BusIO) | I²C/SPI abstraction (dependency) |
| **Adafruit BME280** | [GitHub](https://github.com/adafruit/Adafruit_BME280_Library) | Climate sensor driver |
| **Servo** | [Arduino Docs](https://docs.arduino.cc/libraries/servo/) | Servo motor control |
| **Wire** | Built-in | I²C communication |
| **SPI** | Built-in | SPI communication |

Install all libraries via the **Arduino IDE Library Manager** or clone them into your `libraries/` folder.

### Project Structure

```text
greenhouse/
├── README.md                # Project documentation
├── LICENSE                  # MIT License
├── greenhouse.ino           # Main firmware source code
├── 3D/                      # 3D-printable parts (*.stl)
├── laser/                   # Laser-cut templates (*.svg)
└── docs/                    # Additional documentation
    ├── images/              # Documentation images
    ├── Greenhouse Presentation.pptx # Project presentation
    ├── netlist.xml          # Fritzing netlist export
    ├── schematic.fzz        # Fritzing project file
    └── schematic.png        # Wiring schematic export
```

---

## Flashing

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Connect the Arduino Nano via USB.
3. In **Tools → Board**, select **Arduino Nano**.
4. In **Tools → Processor**, select **ATmega328P** (or **ATmega328P (Old Bootloader)** if upload fails).
5. Select the correct **COM port** under **Tools → Port**.
6. Install all [dependencies](#dependencies) via **Sketch → Include Library → Manage Libraries**.
7. Open `greenhouse.ino` and click **Upload** (→).

---

## How It Works

```
┌──────────────────────────────────────────────────┐
│                  Arduino Nano                    │
│                                                  │
│  Soil Moisture (A6) ──► too dry? ──► Relay (D7)  │
│                                     └──► Pump ON │
│                                                  │
│  Photodiode (D2) ────► dark? ────► RGB LED       │
│                                     (D4/D5/D6)   │
│                                     └──► Fade FX │
│                                                  │
│  BME280 (I²C) ───────► read T/H/P                │
│                         └──► Display (I²C)       │
│                                                  │
│  Servo (D3) ─────────► humidity high?            │
│                         └──► Open window         │
└──────────────────────────────────────────────────┘
```

### Configuration

Key thresholds and timings are defined at the top of `greenhouse.ino`:

```cpp
// Soil moisture validation
#define MOISTURE_THRESHOLD 400 // From 0 to 400 = wet soil, Above 400 = dry soil

// Climate limits for window automated control
const int max_temp = 25;       // Open window if temp > max_temp
const int min_temp = 18;       // Close window if temp < min_temp
const int temp_margin = 2;     // Hysteresis margin
const int max_hum = 70;        // Open window if humidity > max_hum
const int min_hum = 50;        // Close window if humidity < min_hum
const int hum_margin = 5;      // Hysteresis margin

// Servo angles
const int window_close_pos = 90;
const int window_open_pos = 180;

// Update intervals (in milliseconds)
const unsigned long SENSOR_INTERVAL_MS = 1000;  // Measure sensors every 1s
const unsigned long DISPLAY_INTERVAL_MS = 3000; // Cycle display pages every 3s
const unsigned long DISCO_INTERVAL_MS = 10;     // Update LED colors every 10ms
```

---

## Credits

This project was developed as part of the **Erasmus 2026** program — a collaborative exchange between German and Spanish students and teachers, organized by the engineering office **IngGreen**.

Special thanks to all participants and mentors who contributed to the design, development, and documentation of this prototype.

---

## License

This project is licensed under the [MIT License](LICENSE).

