#include "../driver/fan_driver.h"

int main()
{
    FanDriver fan;

    if (!fan.initialize())
    {
        return 1;
    }

    fan.setFanSpeed(0);
    fan.setFanSpeed(30);
    fan.setFanSpeed(50);
    fan.setFanSpeed(75);
    fan.setFanSpeed(100);

    fan.shutdown();

    return 0;
}
