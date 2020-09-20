// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

class ILasers
{
public:
    virtual float readF() = 0;
    virtual float computeFrontAngle() = 0;
    virtual float readFL() = 0;
    virtual float readFR() = 0;
    virtual float readL() = 0;
    virtual float readR() = 0;
    virtual float readB() = 0;
    virtual ~ILasers() = default;
};
