// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

enum MovementState
{
    SUCCESS,
    RAMP,
    BLACK
};

class IDriver
{
public:
    virtual void rotate(bool right) = 0;
    virtual void go() = 0;
};
