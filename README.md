# Industrial Thermal Management & Dynamic Fan Controller

A software-based Embedded Linux project that monitors temperature, dynamically controls fan speed, detects critical thermal conditions, and safely shuts down the fan controller.

## 📌 Project Overview

The **Industrial Thermal Management & Dynamic Fan Controller** is designed to demonstrate an automated thermal management system running on Linux.

The system continuously monitors temperature, determines the corresponding thermal status, calculates the required fan speed, sends the speed command to a simulated PWM fan driver, and records thermal information in a CSV log.

The project is implemented in **C++** using a modular architecture and is developed and tested in an Embedded Linux environment.

## 🎯 Objectives

- Monitor system temperature
- Dynamically control fan speed
- Use configurable temperature thresholds
- Detect high, critical, and emergency thermal conditions
- Simulate PWM-based fan control
- Maintain thermal operation logs
- Provide graceful system shutdown
- Test individual and integrated components

## 🏗️ System Architecture

```text
        Temperature Source
              |
              v
      +------------------+
      | Thermal Monitor  |
      +------------------+
              |
              v
      +------------------+
      | Fan Controller   |
      +------------------+
              |
              v
      +------------------+
      |   Fan Driver     |
      |  PWM Simulation  |
      +------------------+
              |
              v
        Fan Operation

              |
              +--------------------+
              |                    |
              v                    v
       Thermal Status         CSV Logging
              |
              v
      Emergency Detection
```

## ⚙️ Main Features

### 1. Temperature Monitoring

The system obtains temperature data through the thermal monitoring module.

For development and testing, a simulated temperature source is also available.

### 2. Dynamic Fan Control

Fan speed is automatically calculated according to the configured temperature thresholds.

| Temperature | Fan Speed | Status |
|---|---:|---|
| Below 45°C | 0% | LOW |
| 45–54°C | 30% | NORMAL |
| 55–64°C | 50% | NORMAL |
| 65–74°C | 75% | HIGH |
| 75–84°C | 100% | CRITICAL |
| 85°C and above | 100% | EMERGENCY |

### 3. Emergency Detection

When the temperature reaches the configured emergency threshold, the system displays an emergency warning and maintains maximum fan speed.

```text
Temperature >= 85°C
        |
        v
   EMERGENCY
        |
        v
   Fan = 100%
```

### 4. Thermal Logging

The system records:

- Timestamp
- Temperature
- Fan speed
- Thermal status

Logs are stored in:

```text
logs/thermal_log.csv
```

### 5. Graceful Shutdown

The application handles `SIGINT` and `SIGTERM`.

When `Ctrl+C` is pressed:

```text
Ctrl+C
  ↓
Signal received
  ↓
Monitoring loop stops
  ↓
Fan driver shutdown
  ↓
Fan speed = 0%
  ↓
System stopped safely
```

## 🧪 Testing

The project includes unit tests for the fan controller.

Run:

```bash
make test
```

Example test cases:

```text
Temperature: 40 | Fan: 0   | Status: LOW       | PASS
Temperature: 50 | Fan: 30  | Status: NORMAL    | PASS
Temperature: 60 | Fan: 50  | Status: NORMAL    | PASS
Temperature: 70 | Fan: 75  | Status: HIGH      | PASS
Temperature: 80 | Fan: 100 | Status: CRITICAL  | PASS
Temperature: 90 | Fan: 100 | Status: EMERGENCY | PASS
```

## 🔨 Build and Run

### Build

```bash
make
```

### Run

```bash
./thermal_controller
```

### Run Tests

```bash
make test
```

### Clean Build Files

```bash
make clean
```

## 📁 Project Structure

```text
Industrial-Thermal-Management/
│
├── config/
│   └── config.txt
│
├── docs/
│   ├── stage1-project-introduction.md
│   ├── stage2-thermal-controller.md
│   ├── stage3-system-design.md
│   ├── stage4-initial-implementation.md
│   ├── stage5-testing-integration.md
│   └── stage6-finalization.md
│
├── driver/
│   ├── fan_driver.cpp
│   └── fan_driver.h
│
├── include/
│   ├── fan_controller.h
│   └── thermal_monitor.h
│
├── logs/
│   └── thermal_log.csv
│
├── src/
│   ├── main.cpp
│   ├── thermal_monitor.cpp
│   └── fan_controller.cpp

├── tests/
│   ├── test_fan_controller.cpp
│   └── test_fan_driver.cpp│

├── Makefile
└── README.md
```

## 🛠️ Technology Stack

- **Operating System:** Linux
- **Programming Language:** C++
- **Compiler:** G++
- **Build System:** GNU Make
- **Version Control:** Git & GitHub
- **Testing:** C++ unit tests
- **Hardware Interface:** Simulated PWM fan driver
- **Data Storage:** CSV logging
## 🐧 Linux Device Driver Concepts

The project demonstrates Linux device-driver concepts through a modular user-space fan driver abstraction.

The `driver/fan_driver.cpp` and `driver/fan_driver.h` modules represent the fan hardware interface and simulate PWM-based fan-speed control.

The driver provides:
- Fan driver initialization
- PWM output simulation
- Fan speed control from 0% to 100%
- Input range validation and clamping
- Driver shutdown
- Hardware-interface abstraction

This project uses a simulated user-space driver rather than a Linux kernel module, allowing the thermal-management architecture to be developed and tested safely in a Linux environment.
## 📚 Project Stages

| Stage | Description |
|---|---|
| Stage 1 | Project Introduction |
| Stage 2 | Thermal Controller Design |
| Stage 3 | System Design |
| Stage 4 | Initial Implementation |
| Stage 5 | Testing, Integration & Improvements |
| Stage 6 | Finalization & Demonstration |

## 🚀 Future Improvements

The system can be extended with:

- Real temperature sensor integration
- Real GPIO/PWM fan control
- Raspberry Pi or other embedded-board deployment
- LCD monitoring interface
- Web-based monitoring dashboard
- Real-time temperature graphs
- Fan-speed feedback
- Systemd service integration
- Automatic startup at boot

## 👨‍💻 Project Status

**Status: Completed**

The system has been implemented, tested, integrated, documented, and prepared for final demonstration.

## 📄 Documentation

Detailed documentation for each development stage is available in the `docs/` directory.

## 📜 License

This project is developed for academic and educational purposes.# Industrial-Thermal-Management
