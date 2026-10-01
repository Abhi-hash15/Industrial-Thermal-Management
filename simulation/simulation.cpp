#include "simulation.h"

#include "../include/fan_controller.h"
#include "../include/thermal_monitor.h"
#include "../driver/fan_driver.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <string>

namespace
{
    void printBar(const std::string& label, double value, int maxValue)
    {
        const int width = 40;

        int filled =
            static_cast<int>((value / maxValue) * width);

        if (filled < 0)
            filled = 0;

        if (filled > width)
            filled = width;

        std::cout << std::left
                  << std::setw(16)
                  << label
                  << "[";

        for (int i = 0; i < width; ++i)
        {
            if (i < filled)
                std::cout << "#";
            else
                std::cout << "-";
        }

        std::cout << "] " << value << std::endl;
    }

    void clearScreen()
    {
        std::cout << "\033[2J\033[H";
    }
}

void runSimulation()
{
    ThermalConfig config{};

    if (!loadConfig("config/config.txt", config))
    {
        std::cerr << "Error: Unable to load configuration.\n";
        return;
    }

    FanDriver fan;

    if (!fan.initialize())
    {
        std::cerr << "Error: Fan driver initialization failed.\n";
        return;
    }

    std::cout << "\nStarting Industrial Thermal Simulation...\n";
    std::this_thread::sleep_for(
        std::chrono::seconds(2)
    );

    for (int cycle = 0; cycle < 50; ++cycle)
    {
        double temperature = getSimulatedTemperature();

        int fanSpeed =
            calculateFanSpeed(temperature, config);

        const char* status =
            getThermalStatus(temperature, config);

        fan.setFanSpeed(fanSpeed);

        clearScreen();

        std::cout
            << "====================================================\n"
            << "       INDUSTRIAL THERMAL MANAGEMENT SIMULATOR\n"
            << "====================================================\n\n";

        std::cout
            << " Simulation Cycle : "
            << cycle + 1
            << "\n\n";

        std::cout
            << " Temperature      : "
            << std::fixed
            << std::setprecision(2)
            << temperature
            << " °C\n";

        std::cout
            << " Fan Speed        : "
            << fanSpeed
            << " %\n";

        std::cout
            << " Thermal Status   : "
            << status
            << "\n";

        if (temperature >= config.emergencyTemp)
        {
            std::cout
                << "\n"
                << " !!! EMERGENCY !!!\n"
                << " Temperature limit exceeded!\n"
                << " Fan running at maximum speed.\n";
        }
        else if (temperature >= config.criticalTemp)
        {
            std::cout
                << "\n"
                << " !!! CRITICAL TEMPERATURE !!!\n";
        }

        std::cout << "\n----------------------------------------------------\n";

        printBar(
            "Temperature",
            temperature,
            100
        );

        printBar(
            "Fan PWM",
            fanSpeed,
            100
        );

        std::cout
            << "\n----------------------------------------------------\n"
            << " Thermal Thresholds\n"
            << "----------------------------------------------------\n"
            << " LOW       : < 45 °C\n"
            << " NORMAL    : 45 - 64 °C\n"
            << " HIGH      : 65 - 74 °C\n"
            << " CRITICAL  : 75 - 84 °C\n"
            << " EMERGENCY : >= 85 °C\n"
            << "----------------------------------------------------\n";

        std::cout
            << "\n [SIMULATION RUNNING]"
            << "\n Press Ctrl+C to stop.\n";

        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }

    fan.shutdown();

    std::cout
        << "\nSimulation completed successfully.\n";
}
