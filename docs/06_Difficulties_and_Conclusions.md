# Difficulties and Conclusions

While the Erasmus 2026 greenhouse project concluded successfully with entirely functional automation, the 3-week timeline experienced severe bottlenecks primarily rooted in hardware logistics and systemic discrepancies.

## Primary Challenges

- **Hardware Procurement and Delivery Delays**: The instructor placed an order for electronic components that ultimately proved inconsistent with the initial parts list drafted in Week 1. This discrepancy required rapid architectural recalibration. Additionally, these substitute parts did not arrive until Wednesday of the second week. By the time physical assembly and breadboard validation could begin, almost half of the development schedule had expired.
- **Self-Funded Component Replacement**: Instead of rewriting the software stack to accommodate the incorrect parts, the team decided to proactively order the correct actuators and logic components at their own expense. This ensured the hardware remained true to the initial design but added further time pressure to the development cycle.
- **Physical Assembly Compression**: Due to the cascading delays, finalizing the 3D prints (Pillars, Bases) and laser-cutting the Plexiglas sections (Roof, Windows) was compressed heavily into the remaining days of Week 3, leaving minimal margins for error. The glass mounting and servo alignments on the `Pillar Top` required particular mechanical exactness that was difficult to iterate within hours.

## Conclusions

Despite encountering severe hardware delivery delays, incorrect components, and a heavily compressed testing phase, the development team leveraged effective Scrum paradigms, modular design, and robust coding principles to complete all features.
The automated irrigation logic functions reliably alongside the complex BME280 hysteresis cooling cycle, while aesthetic flourishes—like the gamma-corrected RGB LED sequencing—demonstrate professional execution. The outcome validated the collaborative ability of the Spanish and German teams and provided excellent hands-on mechanical and electrical insight.