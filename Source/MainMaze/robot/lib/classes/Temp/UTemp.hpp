#pragma once
#include "MainMaze/DrivableActor.h"
#include "MainMaze/robot/lib/interfaces/ITemp.hh"

class UTemp : public ITemp
{
public:
    UTemp(DrivableActor* DrivableActor);
    void calibrate() override;
    GeometricPair<float> read() override;
    GeometricPair<bool> isHot() override;

private:
    DrivableActor* Actor;
    float ReadSide(FVector Direction);
};
