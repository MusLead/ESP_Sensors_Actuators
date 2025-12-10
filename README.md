# ESP_Sensors_Actuators (submodule for Smart-Home-Ventilation)

This repository contains reusable ESP-based sensor and actuator code intended to be included as a git submodule in the Smart-Home-Ventilation project:
https://github.com/MusLead/Smart-Home-Ventilation

This README explains the purpose of this submodule, what it contains, and how to integrate it into the Smart-Home-Ventilation repository.

## Overview

ESP_Sensors_Actuators provides:
- Drivers and helper code for common sensors used in home ventilation (e.g., temperature, humidity, CO2/TVOC, pressure).
- Actuator interfaces for fans, dampers, relays, and PWM-based devices.
- Abstracted initialization and configuration utilities to make integration with a higher-level controller (like Smart-Home-Ventilation) straightforward.
- Example wiring and example sketches or components for PlatformIO / ESP-IDF / Arduino frameworks.

This repository is intentionally framework-agnostic and structured to be added as a submodule so the main Smart-Home-Ventilation project can import only what it needs.

## Repository contents (high level)

- src/ — sensor and actuator implementations
- include/ — public header files and API surface
- examples/ — small examples showing how to use the library (PlatformIO, Arduino, ESP-IDF)
- docs/ — wiring diagrams, pin recommendations, configuration notes
- LICENSE — licensing information

(If your copy differs, follow the files that shipped in this submodule.)

## Requirements

- ESP8266 or ESP32 toolchain (PlatformIO, Arduino, or ESP-IDF)
- Relevant sensor/actuator libraries (listed in examples or platform config)
- Smart-Home-Ventilation expects this repository to be available as a submodule (see integration steps)

## Adding as a submodule

From the root of the Smart-Home-Ventilation repository, add this repository as a submodule:

git submodule add https://github.com/MusLead/ESP_Sensors_Actuators.git libs/ESP_Sensors_Actuators
git submodule update --init --recursive

Notes:
- The path `libs/ESP_Sensors_Actuators` is only a suggested location. Adjust the path in your project if you prefer `components/`, `lib/`, or another layout.
- After cloning Smart-Home-Ventilation, use `git submodule update --init --recursive` to fetch this submodule.

