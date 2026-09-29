# Stage 3 – System Design & Architecture

## 1. System Overview

The Industrial Thermal Management & Dynamic Fan Controller is a Linux-based
thermal monitoring and fan control system developed using C++17.

The system continuously monitors temperature, determines the thermal state,
and dynamically controls the fan speed using a simulated PWM fan driver.

The project is designed to demonstrate Linux system programming, device
driver interaction, C++ programming, file handling, logging, and version
control.

---

## 2. System Architecture

The overall system follows this flow:

Temperature Monitor
        |
        v
Thermal Control / Fan Controller
        |
        v
Simulated Fan Driver
        |
        v
PWM Fan Output

The Linux operating system provides the environment for the application,
file interfaces, system calls, logging, and device interaction.

### Architecture Components

1. Temperature Monitor
2. Fan Controller
3. Simulated Fan Driver
4. PWM Fan Output
5. CSV Logger
6. Linux Thermal Interface

---

## 3. Component Responsibilities

### 3.1 Temperature Monitor

Responsibilities:

- Read temperature values.
- Validate temperature data.
- Provide current temperature to the controller.
- Detect abnormal temperature values.

### 3.2 Fan Controller

Responsibilities:

- Analyze the current temperature.
- Determine the thermal state.
- Calculate the required fan speed.
- Send the fan-speed command to the fan driver.

### 3.3 Simulated Fan Driver

Responsibilities:

- Simulate a Linux fan device.
- Receive fan-speed commands.
- Represent PWM-based fan control.
- Provide an interface between the application and fan output.

### 3.4 PWM Fan Output

Responsibilities:

- Represent the final fan-speed output.
- Convert the requested speed into a PWM percentage.
- Simulate fan operation in the software environment.

### 3.5 CSV Logger

Responsibilities:

- Record temperature readings.
- Record fan speed.
- Record thermal state.
- Record system events and errors.

### 3.6 Linux Thermal Interface

Responsibilities:

- Provide the Linux thermal data interface.
- Support interaction between the application and Linux thermal subsystem.
- Provide a software-based interface for temperature monitoring.

---

## 4. Thermal Control Logic

The controller uses temperature ranges to determine the fan speed.

| Temperature | Thermal State | Fan Speed |
|-------------|---------------|-----------|
| Below 40°C | NORMAL | 20% |
| 40°C–55°C | WARM | 40% |
| 55°C–70°C | HOT | 70% |
| Above 70°C | CRITICAL | 100% |

These values can be modified during Stage 5 testing and optimization.

---

## 5. Required Data Structures

### TemperatureData

Stores temperature information.

```cpp
struct TemperatureData {
    float temperature;
    long timestamp;
};
---

## 16. Stage 3 Progress Evidence

The following activities were completed during Stage 3:

- System architecture was designed and documented.
- Major system components and their responsibilities were identified.
- Required C++ data structures were defined.
- Class Diagram was prepared.
- Sequence Diagram was prepared.
- State Machine Diagram was prepared.
- Implementation plan for Stage 4 was defined.
- Ubuntu Linux development environment was verified.
- GNU g++ 13.3.0 was verified.
- GNU Make 4.3 was verified.
- Git 2.43.0 was verified.
- Git repository was configured with a dedicated `stage3` branch.
- Stage 3 documentation was committed to Git.
- Stage 3 branch was successfully pushed to GitHub.

### Git Information

- **Branch:** `stage3`
- **Commit:** `19518d7`
- **Commit Message:** `Add Stage 3 system design and architecture`
- **Remote Branch:** `origin/stage3`

### Progress Evidence

The following evidence was captured during Stage 3:

1. Project repository containing Stage 1 and Stage 2 documentation.
2. Ubuntu development environment with g++, Make and Git.
3. Creation of the `stage3` Git branch.
4. Stage 3 documentation commit.
5. Successful push of the `stage3` branch to GitHub.

---

## 17. Roadmap for Stage 4

Stage 4 will focus on the initial implementation and working prototype.

Planned activities:

1. Implement the Temperature Monitor.
2. Implement the Fan Controller in C++.
3. Implement the simulated fan driver.
4. Implement PWM fan-speed control.
5. Implement CSV logging.
6. Integrate the major modules.
7. Build the project using the Makefile.
8. Run the initial working prototype.
9. Demonstrate temperature-based fan-speed control.
10. Record implementation issues and solutions.
