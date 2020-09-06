#pragma once

class IGyro
{
public:
    IGyro();
    void begin(AActor* TMainCharacter);
    bool checko();
    void start(unsigned long refresh);
    float yaw();
    float roll();
    float pitch();
    // float getTemperature();
    void calibrate();
};
