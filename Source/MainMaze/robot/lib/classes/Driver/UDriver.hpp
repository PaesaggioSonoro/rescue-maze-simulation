#pragma once
#include "MainMaze/DrivableActor.h"
#include "MainMaze/robot/lib/interfaces/IDriver.hh"

class UDriver : public IDriver
{
public:
    UDriver(DrivableActor* DrivableActor);
    void rotate(bool right) override;
    void go() override;

private:
    DrivableActor* Actor;
    static bool RightTurnCondition(float Start, float Current, float Goal);
    static bool LeftTurnCondition(float Start, float Current, float Goal);
};
