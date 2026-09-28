#ifndef FAN_DRIVER_H
#define FAN_DRIVER_H

class FanDriver
{
public:
    FanDriver();

    bool initialize();
    void setFanSpeed(int percentage);
    int getFanSpeed() const;
    void shutdown();

private:
    int currentSpeed;
    bool initialized;
};

#endif
