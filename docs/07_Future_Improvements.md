# Future Improvements

While the current implementation covers every planned feature for a smart greenhouse—soil moisture readings, climate response, and ambient lighting—future models possess immense room for further expansion.

## Microcontroller Migration (IoT Focus)
A critical limitation of the Arduino Nano ATmega328P is its lack of wireless connectivity. A fundamental upgrade involves replacing it with a Wi-Fi-enabled System on a Chip (SoC), such as the **ESP32** or **ESP8266**. This would enable remote monitoring, long-term historical data graphing for plant vitality analysis, and mobile push notifications for water tank reservoirs.
In parallel, establishing a mobile-friendly **Web UI** (User Interface) could display live parameters and toggle manual intervention via simple HTTP requests.

## Modularity and Energy Efficiency
- **Autonomous Power Structures**: Replacing the 9V disposable batteries with rechargeable Lithium-Ion standard (18650) cells and solar panels on the roof could dramatically increase the sustainability of the system over the long term.
- **Deep Sleep Cycles**: Instead of constant non-blocking loops, adapting the system to place the microcontroller and BME280 into a deep sleep, waking periodically to ping the moisture inputs or environmental logic, could prolong life exponentially.
- **Water Level Sensor**: Installing an ultrasonic or float sensor strictly inside the water tank could interrupt the `digitalWrite(rele_pin, LOW)` command and generate an alarm to prevent the pump from "running dry" and potentially sustaining thermal damage.