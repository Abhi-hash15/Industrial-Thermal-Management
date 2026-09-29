#include "../include/fan_controller.h"
#include <iostream>
#include <string>

void check(double temp, int expectedFan, const char* expectedStatus,
           const ThermalConfig& config)
{
    int fan = calculateFanSpeed(temp, config);
    const char* status = getThermalStatus(temp, config);

    std::cout << "Temperature: " << temp
              << " | Fan: " << fan
              << " | Status: " << status;

    if (fan == expectedFan &&
        std::string(status) == expectedStatus)
    {
        std::cout << " | PASS\n";
    }
    else
    {
        std::cout << " | FAIL"
                  << " (Expected Fan: " << expectedFan
                  << ", Status: " << expectedStatus << ")\n";
    }
}

int main()
{
    ThermalConfig config{
        45.0,
        55.0,
        65.0,
        75.0,
        85.0
    };

    check(40, 0,   "LOW",       config);
    check(50, 30,  "NORMAL",    config);
    check(60, 50,  "NORMAL",    config);
    check(70, 75,  "HIGH",      config);
    check(80, 100, "CRITICAL",  config);
    check(90, 100, "EMERGENCY", config);

    return 0;
}
