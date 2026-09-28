#include "fan_driver.h"

#include <iostream>

FanDriver::FanDriver()
    : currentSpeed(0), initialized(false)
{
}

bool FanDriver::initialize()
{
    initialized = true;

    std::cout << "[FAN DRIVER] Initialized successfully."
              << std::endl;

    return true;
}

void FanDriver::setFanSpeed(int percentage)
{
    if (!initialized)
    {
        std::cerr << "[FAN DRIVER] Error: Driver not initialized."
                  << std::endl;
        return;
    }

    if (percentage < 0)
        percentage = 0;

    if (percentage > 100)
        percentage = 100;

    currentSpeed = percentage;

    std::cout << "[FAN DRIVER] PWM Output: "
              << currentSpeed
              << "%" << std::endl;
}

int FanDriver::getFanSpeed() const
{
    return currentSpeed;
}

void FanDriver::shutdown()
{
    if (initialized)
    {
        currentSpeed = 0;
        initialized = false;

        std::cout << "[FAN DRIVER] Fan stopped. Driver shutdown."
                  << std::endl;
    }
}
