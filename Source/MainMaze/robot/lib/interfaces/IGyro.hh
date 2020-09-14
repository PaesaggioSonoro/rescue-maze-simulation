// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

class IGyro
{
public:
    virtual void start(unsigned long refresh) = 0;
    virtual float yaw() = 0;
    virtual float roll() = 0;
    virtual float pitch() = 0;
    virtual void calibrate() = 0;
    virtual ~IGyro() = default;
};
