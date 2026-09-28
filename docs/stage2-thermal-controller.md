# Stage 2 - Industrial Thermal Management & Dynamic Fan Controller

## 1. Objective

The objective of Stage 2 is to implement the core thermal management and dynamic fan control system using C++ on Embedded Linux.

The system monitors temperature, determines the required fan speed, generates simulated PWM output, logs thermal data, and provides emergency over-temperature protection.

## 2. Technologies Used

- C++
- C++17
- GNU g++
- Embedded Linux / Ubuntu
- Linux thermal interface
- Makefile
- CSV logging
- Simulated PWM fan driver

## 3. System Architecture

```text
Temperature Monitor
        |
        v
Fan Controller
        |
        v
Fan Driver
        |
        v
PWM Fan Output
