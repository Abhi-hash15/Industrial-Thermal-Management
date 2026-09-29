#include "../driver/fan_driver.h"
#include <iostream>

bool checkSpeed(FanDriver& fan, int requested, int expected)
{
    fan.setFanSpeed(requested);

    int actual = fan.getFanSpeed();

    std::cout << "Requested: " << requested
              << "% | Actual: " << actual << "%";

    if (actual == expected)
    {
        std::cout << " | PASS\n";
        return true;
    }

    std::cout << " | FAIL\n";
    return false;
}

int main()
{
    FanDriver fan;

    if (!fan.initialize())
    {
        std::cout << "Fan driver initialization failed.\n";
        return 1;
    }

    bool passed = true;

    passed &= checkSpeed(fan, 0, 0);
    passed &= checkSpeed(fan, 30, 30);
    passed &= checkSpeed(fan, 50, 50);
    passed &= checkSpeed(fan, 75, 75);
    passed &= checkSpeed(fan, 100, 100);

    // Test lower boundary
    passed &= checkSpeed(fan, -10, 0);

    // Test upper boundary
    passed &= checkSpeed(fan, 120, 100);

    fan.shutdown();

    if (passed)
    {
        std::cout << "\nAll fan driver tests passed.\n";
        return 0;
    }

    std::cout << "\nFan driver test failed.\n";
    return 1;
}
