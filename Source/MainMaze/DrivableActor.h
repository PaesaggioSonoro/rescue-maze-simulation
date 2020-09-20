#pragma once

#include "CoreMinimal.h"

class DrivableActor
{
public:
    virtual ~DrivableActor() = default;

    virtual AActor* GetActor() = 0;

    // Actuation
    virtual void SetSpeedR(int speed) = 0;
    virtual void SetSpeedL(int speed) = 0;
    virtual void SetSpeed(int speedL, int speedR) = 0;
};
