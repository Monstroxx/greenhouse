# Extended Documentation Index

This directory contains the professional, detailed documentation for the Greenhouse project. Browse the sections below to understand the technical and organizational aspects.

- **[01 Project Overview](01_Project_Overview.md)**  
  High-level academic description of the systems, purpose, and final assembly of the greenhouse.

- **[02 Features and Theory](02_Features_and_Theory.md)**  
  Thorough explanations on how the irrigation loop, window hysteresis boundaries, and gamma-corrected RGB LED simulations operate.

- **[03 Components and Hardware](03_Components_and_Hardware.md)**  
  Details of every sensor (BME280, Photodiode, Moisture), actuator (Pump, Servo), and structure (3D-printed parts) alongside physical breadboarding images and Fritzing schematics.

- **[04 Planning and Collaboration](04_Planning_and_Collaboration.md)**  
  Breakdown of the 3-week Erasmus exchange using Agile/Scrum methods (Trello, Sprint stories) to coordinate between the German and Spanish team members.

- **[05 Software Architecture](05_Software_Architecture.md)**  
  Under-the-hood logic detailing why standard delays were bypassed in favor of dynamic `millis()` loop counters.

- **[06 Difficulties and Conclusions](06_Difficulties_and_Conclusions.md)**  
  A recap of the hardware delays (and the team's self-funded workaround) that severely constrained the build time.

- **[07 Future Improvements](07_Future_Improvements.md)**  
  Pathways for optimizing energy efficiency, integrating Wi-Fi IoT boards (ESP32), and establishing a Web UI.

> *Note: For the firmware logic itself, please refer directly to the root source file:* **[`../greenhouse.ino`](../greenhouse.ino)**