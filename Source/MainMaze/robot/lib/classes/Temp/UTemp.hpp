#pragma once
#include "MainMaze/DrivableActor.h"
#include "MainMaze/robot/lib/interfaces/ITemp.hh"

class UTemp : public ITemp
{
public:
    UTemp(DrivableActor* actor);
    void calibrate() override;
    GeometricPair<float> read() override;
    GeometricPair<bool> isHot() override;

private:
    DrivableActor* actor;
    float readSide(FVector direction);
};
