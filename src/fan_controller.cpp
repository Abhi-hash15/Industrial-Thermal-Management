#include "../include/fan_controller.h"

#include <fstream>
#include <sstream>
#include <string>

bool loadConfig(const char* filename, ThermalConfig& config)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string key;
        std::string value;

        if (std::getline(ss, key, '=') &&
            std::getline(ss, value))
        {
            double number = std::stod(value);

            if (key == "LOW_TEMP")
                config.lowTemp = number;
            else if (key == "MEDIUM_TEMP")
                config.mediumTemp = number;
            else if (key == "HIGH_TEMP")
                config.highTemp = number;
            else if (key == "CRITICAL_TEMP")
                config.criticalTemp = number;
            else if (key == "EMERGENCY_TEMP")
                config.emergencyTemp = number;
        }
    }

    return true;
}

int calculateFanSpeed(
    double temperature,
    const ThermalConfig& config)
{
    if (temperature < config.lowTemp)
    {
        return 0;
    }
    else if (temperature < config.mediumTemp)
    {
        return 30;
    }
    else if (temperature < config.highTemp)
    {
        return 50;
    }
    else if (temperature < config.criticalTemp)
    {
        return 75;
    }
    else
    {
        return 100;
    }
}

const char* getThermalStatus(
    double temperature,
    const ThermalConfig& config)
{
    if (temperature >= config.emergencyTemp)
    {
        return "EMERGENCY";
    }
    else if (temperature >= config.criticalTemp)
    {
        return "HIGH";
    }
    else if (temperature >= config.mediumTemp)
    {
        return "NORMAL";
    }
    else
    {
        return "LOW";
    }
}
