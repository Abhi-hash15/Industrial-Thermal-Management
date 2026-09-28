#include "../include/thermal_monitor.h"

#include <fstream>
#include <string>

double getCpuTemperature()
{
    const std::string thermalPath =
        "/sys/class/thermal/thermal_zone0/temp";

    std::ifstream file(thermalPath);

    if (!file.is_open())
    {
        return -1.0;
    }

    long temperature;
    file >> temperature;

    return temperature / 1000.0;
}

double getSimulatedTemperature()
{
    static double temperature = 40.0;

    temperature += 2.0;

    if (temperature > 90.0)
    {
        temperature = 40.0;
    }

    return temperature;
}
