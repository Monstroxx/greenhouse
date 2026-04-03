# Planning and Collaboration

The Erasmus 2026 exchange program was structured around a strict 3-week timeline requiring rapid prototyping, clear communication, and efficient task division among international students. To handle the complexity of language and specialized engineering tasks, the team adopted the Agile development methodology, specifically Scrum.

## Project Management and Roles

The development group utilized shared digital tools to manage resources, code bases, and daily tasks:

- **Rafa Lebrón**: Operated as the Scrum Master, ensuring the team adhered to the Sprint Backlog and resolving blockers before they affected development times.
- **Alex**: Functioned as the Designer, translating conceptual structures into concrete CAD components.
- **TagerTi**: Acted as a Programmer, responsible for the initial firmware loops and hardware prototyping.
- **Monstroxx**: Served as a Programmer, integrating sensor logic, debugging loop iterations, and establishing the final software stack.

## Collaboration Tools

A robust toolchain enabled seamless tracking and execution:
- **Trello (Kanban)**: Maintained for continuous integration of User Stories (such as "Greenhouse Design," "Microcontroller Installation," and "Display Sensor Data") against active `Sprint` cycles. 
- **Google Drive**: Served as the centralized repository for shared documents, CAD prototypes, and weekly reports.
- **GitHub**: Ensured version control for the `greenhouse.ino` source code and overarching documentation.
- **Pytha and Onshape**: Supported parametric 3D modeling and laser-cutting exports (`.svg`) for the physical superstructure.
- **Fritzing**: Used collaboratively to verify electrical boundaries and draft the system's `netlist.xml` before soldering commenced.
- **Arduino IDE**: Handled the native C++ compiling and flashing cycles onto the ATmega328P.

## Milestone Breakdown

### Week 1: Ideation and Structuring
The first week focused entirely on architectural scoping. The team successfully created conceptual blueprints, established the Agile Kanban boards on Trello, integrated shared Drive folders, and visited CosmoCaixa for thematic inspiration. By Thursday, precise component locations were mapped using Fritzing.

### Week 2: Initial Implementation and Logistics
Hardware realization began by translating 3D models into PLA prints via the school's facilities. The Scrum Master and Designer pushed to finalize baseplate topologies. Despite significant delays caused by the late delivery of primary electrical systems (which did not arrive until Wednesday), the Programmers adapted swiftly. By Thursday, initial sensor integration (`OLED`, `BME280`, `Moisture`, and `Photodiode`) alongside fundamental LED behaviors were reliably compiled. 

### Week 3: Final Assembly and Integration
The final days synthesized software and hardware. Actuators alongside the acrylic (Plexiglas) roof structures were cut out via the exported `.svg` files and assembled dynamically. Programmers validated the `Servo` ventilation system algorithms, ensuring sensors and effectors worked in tandem without deadlocks. The intensive exchange concluded on Thursday with a group presentation demonstrating the completely functional prototype system.