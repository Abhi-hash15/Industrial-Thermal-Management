#include "../include/thermal_monitor.h"
#include "../include/fan_controller.h"
#include "../driver/fan_driver.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>

int main()
{
    ThermalConfig config{};

    if (!loadConfig("config/config.txt", config))
    {
        std::cerr << "Error: Unable to load configuration.\n";
        return 1;
    }

    FanDriver fan;

    if (!fan.initialize())
    {
        std::cerr << "Error: Fan driver initialization failed.\n";
        return 1;
    }

    std::ofstream logFile(
        "logs/thermal_log.csv",
        std::ios::app
    );

    if (!logFile.is_open())
    {
        std::cerr << "Error: Unable to open log file.\n";
        fan.shutdown();
        return 1;
    }

    if (logFile.tellp() == 0)
    {
        logFile << "Timestamp,Temperature_C,"
                << "Fan_Speed_Percent,Status\n";
    }

    std::cout << "\nIndustrial Thermal Management System\n";
    std::cout << "------------------------------------\n";
    std::cout << "Configuration loaded successfully.\n";
    std::cout << "Fan driver initialized.\n";
    std::cout << "System started. Press Ctrl+C to stop.\n\n";

    for (int i = 0; i < 30; i++)
    {
        double temperature = getSimulatedTemperature();

        int fanSpeed =
            calculateFanSpeed(temperature, config);

        const char* status =
            getThermalStatus(temperature, config);

        // Send calculated speed to fan driver
        fan.setFanSpeed(fanSpeed);

        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);

        char timestamp[20];

        std::strftime(
            timestamp,
            sizeof(timestamp),
            "%Y-%m-%d %H:%M:%S",
            localTime
        );

        std::cout
            << "[" << timestamp << "] "
            << "Temperature: "
            << std::fixed
            << std::setprecision(2)
            << temperature
            << " °C | Fan: "
            << fanSpeed
            << "% | Status: "
            << status
            << std::endl;

        logFile
            << timestamp << ","
            << temperature << ","
            << fanSpeed << ","
            << status
            << "\n";

        logFile.flush();

        if (temperature >= config.emergencyTemp)
        {
            std::cout
                << "!!! EMERGENCY: Temperature limit exceeded !!!"
                << std::endl;
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(1)
        );
    }

    fan.shutdown();

    std::cout << "\nSystem stopped safely.\n";

    return 0;
}
