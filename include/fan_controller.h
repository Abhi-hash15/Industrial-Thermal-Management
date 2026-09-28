#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

struct ThermalConfig
{
    double lowTemp;
    double mediumTemp;
    double highTemp;
    double criticalTemp;
    double emergencyTemp;
};

bool loadConfig(const char* filename, ThermalConfig& config);

int calculateFanSpeed(
    double temperature,
    const ThermalConfig& config
);

const char* getThermalStatus(
    double temperature,
    const ThermalConfig& config
);

#endif
