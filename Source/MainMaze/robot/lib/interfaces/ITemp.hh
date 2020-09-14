// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once
#include "MainMaze/robot/utils/GeometricPair.hxx"

class ITemp
{
public:
    float threshold = 0;
    virtual void calibrate() = 0;
    virtual GeometricPair<float> read() = 0;
    virtual GeometricPair<bool> isHot() = 0;
};
