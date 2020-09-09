#pragma once

#include "MainMaze/DrivableActor.h"

class IBus
{
public:
#if _EXECUTION_ENVIRONMENT == 0
    virtual DrivableActor* GetBus() = 0;
    virtual void SetBus(DrivableActor* Actor) = 0;
#else
    virtual I2C GetBus() = 0;
#endif
public:
    virtual ~IBus() = default;
};
