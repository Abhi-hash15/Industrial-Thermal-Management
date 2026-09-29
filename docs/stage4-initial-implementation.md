# Stage 4 – Initial Implementation & Prototype

## 1. Stage Overview

Stage 4 focuses on implementing the core modules of the Industrial Thermal Management & Dynamic Fan Controller and creating an initial working prototype.

The main objectives of this stage are:

- Implement the thermal monitoring module.
- Implement dynamic fan-speed control.
- Implement a simulated fan driver.
- Add configurable temperature thresholds.
- Add CSV-based thermal logging.
- Create a Makefile-based build system.
- Develop unit tests for the controller and fan driver.
- Integrate the modules into a working prototype.
- Test emergency temperature handling.

---

## 2. Development Environment

The project was developed and tested in an Ubuntu Linux virtual machine using Oracle VirtualBox.

### Software Environment

- Operating System: Ubuntu Linux 24.04.1 LTS
- Architecture: x86_64
- Compiler: GNU g++ 13.3.0
- C++ Standard: C++17
- Build Tool: GNU Make 4.3
- Version Control: Git
- Repository: GitHub

### Development Tools

The project uses:

- C++
- Linux system interfaces
- Makefile
- Git/GitHub
- CSV logging
- Simulated hardware driver

---

## 3. Implemented Modules

### 3.1 Main Controller

File:

```text
src/main.cpp
```

The main controller integrates all major modules.

The program:

1. Loads the thermal configuration.
2. Initializes the fan driver.
3. Starts CSV logging.
4. Reads simulated temperature values.
5. Calculates the required fan speed.
6. Determines the thermal state.
7. Sends the speed to the fan driver.
8. Displays system status.
9. Records data in the CSV log.
10. Detects emergency temperature conditions.
11. Performs safe shutdown.

### 3.2 Thermal Monitor

Files:

```text
include/thermal_monitor.h
src/thermal_monitor.cpp
```

The thermal monitor provides temperature information to the controller.

The project supports reading CPU temperature through the Linux thermal interface:

```text
/sys/class/thermal/thermal_zone0/temp
```

For the initial prototype, simulated temperature values are used so that the complete control range can be demonstrated without physical hardware.

The simulated temperature increases gradually and resets after reaching the upper test range.

### 3.3 Fan Controller

Files:

```text
include/fan_controller.h
src/fan_controller.cpp
```

The fan controller:

- Loads temperature thresholds from the configuration file.
- Calculates the required fan speed.
- Determines the thermal status.
- Provides the control decision to the main program.

### 3.4 Fan Driver

Files:

```text
driver/fan_driver.h
driver/fan_driver.cpp
```

The fan driver is implemented as a simulated hardware abstraction.

It represents the PWM output that could later be connected to a physical fan controller.

The driver:

- Initializes the fan.
- Accepts fan-speed percentages.
- Clamps values between 0% and 100%.
- Displays the simulated PWM output.
- Provides the current fan speed.
- Performs safe shutdown.

---

## 4. Configuration

Configuration file:

```text
config/config.txt
```

The configured thresholds are:

```text
LOW_TEMP=45
MEDIUM_TEMP=55
HIGH_TEMP=65
CRITICAL_TEMP=75
EMERGENCY_TEMP=85
```

Fan-speed control:

| Temperature Range | Fan Speed |
|---|---:|
| Below 45°C | 0% |
| 45°C–54°C | 30% |
| 55°C–64°C | 50% |
| 65°C–74°C | 75% |
| 75°C and above | 100% |

Thermal status control:

| Temperature Range | Status |
|---|---|
| Below 45°C | LOW |
| 45°C–64°C | NORMAL |
| 65°C–74°C | HIGH |
| 75°C–84°C | CRITICAL |
| 85°C and above | EMERGENCY |

Emergency handling is activated at 85°C and above.

---

## 5. Logging

The system records thermal information in:

```text
logs/thermal_log.csv
```

The CSV file contains:

```text
Timestamp,Temperature_C,Fan_Speed_Percent,Status
```

Each control cycle records the current temperature, calculated fan speed, and thermal status.

This provides evidence of system operation and can be used for later analysis during Stage 5.

---

## 6. Build System

A Makefile is used to simplify compilation and execution.

Available commands:

```bash
make
make test
make run
make clean
```

The `make` command compiles the complete thermal controller using C++17, GNU g++, and warning flags.

The `make test` command compiles and runs the thermal controller test cases.

The fan driver test can also be compiled separately:

```bash
g++ -std=c++17 -Wall -Wextra tests/test_fan_driver.cpp driver/fan_driver.cpp -o fan_driver_test
./fan_driver_test
```

---

## 7. Build and Test Verification

The initial implementation was successfully compiled and tested in the Ubuntu Linux virtual machine.

### Thermal Controller Tests

Six temperature conditions were tested:

| Temperature | Expected Fan | Expected Status | Result |
|---:|---:|---|---|
| 40°C | 0% | LOW | PASS |
| 50°C | 30% | NORMAL | PASS |
| 60°C | 50% | NORMAL | PASS |
| 70°C | 75% | HIGH | PASS |
| 80°C | 100% | CRITICAL | PASS |
| 90°C | 100% | EMERGENCY | PASS |

All thermal controller test cases passed successfully.

### Fan Driver Tests

The fan driver was tested with:

- 0%
- 30%
- 50%
- 75%
- 100%
- Negative input
- Input greater than 100%
- Initialization
- Shutdown

All fan driver test cases passed successfully.

---

## 8. Prototype Execution

The initial prototype was executed successfully using the thermal controller executable.

The prototype generates simulated temperature values and dynamically changes the fan speed according to the configured thresholds.

Example behavior observed during execution:

```text
64°C → 50% → NORMAL
66°C → 75% → HIGH
74°C → 75% → HIGH
76°C → 100% → CRITICAL
84°C → 100% → CRITICAL
86°C → 100% → EMERGENCY
```

When the temperature reaches the emergency threshold, the system displays:

```text
!!! EMERGENCY: Temperature limit exceeded !!!
```

The fan driver then performs a safe shutdown when the prototype finishes execution.

---

## 9. Issues Encountered and Solutions

### Issue 1: Incorrect Thermal Status Mapping

Initially, some temperature ranges were mapped incorrectly.

**Solution:** The thermal status logic was corrected to:

```text
Below 45°C      → LOW
45°C–64°C       → NORMAL
65°C–74°C       → HIGH
75°C–84°C       → CRITICAL
85°C and above  → EMERGENCY
```

### Issue 2: Duplicate Function Definition

During development, `getThermalStatus()` was accidentally defined twice, causing a compilation error.

**Solution:** The duplicate function was removed and the correct implementation was retained.

### Issue 3: Fan Driver Boundary Values

The fan driver needed to safely handle values outside the valid PWM range.

**Solution:** Fan speed values are clamped between 0% and 100%.

### Issue 4: Hardware Dependency

Physical fan hardware was not required for the initial prototype.

**Solution:** A simulated fan driver was implemented as a software abstraction. It represents the PWM output that could later be connected to real hardware.

---

## 10. Stage 4 Completion

The following Stage 4 objectives were completed:

- Core thermal monitoring logic implemented.
- Dynamic fan-speed control implemented.
- Simulated fan driver implemented.
- Configuration file implemented.
- CSV thermal logging implemented.
- Makefile build system implemented.
- Thermal controller tests implemented.
- Fan driver tests implemented.
- Initial prototype successfully executed.
- Emergency condition handling verified.
- Issues encountered during implementation were resolved.

Stage 4 successfully demonstrates the initial working prototype of the Industrial Thermal Management & Dynamic Fan Controller.

---

## 11. Next Stage

Stage 5 will focus on:

- Complete system integration.
- More comprehensive unit testing.
- Integration and system testing.
- Boundary and abnormal-condition testing.
- Performance and reliability improvements.
- Code quality improvements.
- Debugging and fixing remaining issues.
- Updating documentation and Git repository evidence.

The results from Stage 4 will be used as the baseline for Stage 5 testing and improvement.
