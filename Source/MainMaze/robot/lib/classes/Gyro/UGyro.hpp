#pragma once
#include <chrono>
#include <ctime>

#include "MainMaze/MainVehicle.h"
#include "MainMaze/robot/lib/interfaces/IGyro.hh"

using namespace std::chrono;

class UGyro : public IGyro
{
public:
    UGyro(DrivableActor* DrivableActor);
    void start(unsigned long refresh) override;
    float yaw() override;
    float roll() override;
    float pitch() override;
    void calibrate() override;

private:
    float Drift = 1;
    bool bError = false;
    DrivableActor* Actor;
    float CalculateError();
    float Max_Error = 0.0;
};
