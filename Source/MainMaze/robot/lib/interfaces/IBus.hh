// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

#include "MainMaze/DrivableActor.h"

class IBus
{
public:
#if _EXECUTION_ENVIRONMENT == 0
    virtual DrivableActor* getBus() = 0;
    virtual void setBus(DrivableActor* Actor) = 0;
#else
    virtual I2C getBus() = 0;
#endif
public:
    virtual ~IBus() = default;
};
