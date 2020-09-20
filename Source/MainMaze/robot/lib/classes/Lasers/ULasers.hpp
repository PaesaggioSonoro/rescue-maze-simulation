#pragma once
#include "MainMaze/DrivableActor.h"
#include "MainMaze/robot/lib/interfaces/ILasers.hh"

class ULasers : public ILasers
{
public:
    ULasers(DrivableActor* DrivableActor);
    float readF() override;
    float computeFrontAngle() override;
    float readFL() override;
    float readFR() override;
    float readL() override;
    float readR() override;
    float readB() override;

private:
    DrivableActor* Actor;
    // float Read(FVector Vector, FVector Direction);
    float Read(FVector Direction, float DeltaY);
};
