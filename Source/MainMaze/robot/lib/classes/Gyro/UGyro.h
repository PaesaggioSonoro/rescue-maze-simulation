#pragma once
#include <chrono>
#include <ctime>

#include "MainMaze/MainVehicle.h"
#include "MainMaze/robot/lib/interfaces/IGyro.h"

using namespace std::chrono;

class UGyro : public IGyro
{
public:
    UGyro(DrivableActor* actor);
    void start(unsigned long refresh) override;
    float yaw() override;
    float roll() override;
    float pitch() override;
    void calibrate() override;
    
private:
    float drift = 1;
    bool error = 0;
    DrivableActor* actor;
    float CalculateError();
    float max_error = 0.0;
};
