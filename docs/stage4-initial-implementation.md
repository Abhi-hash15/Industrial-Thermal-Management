# Stage 4 – Initial Implementation & Prototype

## 1. Stage Overview

Stage 4 focuses on the initial implementation and working prototype of the Industrial Thermal Management & Dynamic Fan Controller.

The major C++ modules were implemented and integrated to demonstrate temperature monitoring, thermal-state detection, dynamic fan-speed control, simulated PWM output, CSV logging, and emergency handling.

---

## 2. Development Environment

The project was developed and tested in an Ubuntu Linux environment running inside VirtualBox.

### Tools and Technologies

- Ubuntu Linux
- C++17
- GNU g++ 13.3.0
- GNU Make 4.3
- Git 2.43.0
- Embedded Linux thermal interface
- Simulated PWM fan driver
- CSV file logging

---

## 3. Implemented Modules

### 3.1 Temperature Monitor

File:

```text
src/thermal_monitor.cpp
