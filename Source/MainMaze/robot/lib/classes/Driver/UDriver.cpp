#include "UDriver.hpp"


#include "MainMaze/robot/lib/interfaces/IGyro.hh"
#include "MainMaze/robot/lib/interfaces/ILasers.hh"
#include "MainMaze/robot/servicelocator/RobotServiceLocator.hpp"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

UDriver::UDriver(DrivableActor* DrivableActor) : Actor(DrivableActor)
{
}

void UDriver::rotate(bool right)
{
    sptr<IGyro> Gyro = RobotServiceLocator::instance().sl()->getContext()->resolve<IGyro>();
    float Angle = Gyro->yaw();
    if (right)
    {
        Actor->SetSpeed(50, -50);
        while (Gyro->yaw() < Angle + 80)
        {
            FPlatformProcess::Sleep(0.1);
        }
        Actor->SetSpeed(10, -10);
        while (Gyro->yaw() < Angle + 90)
        {
            FPlatformProcess::Sleep(0.1);
        }
    }
    else
    {
        Actor->SetSpeed(-50, 50);
        while (Gyro->yaw() > Angle - 80)
        {
            FPlatformProcess::Sleep(0.1);
        }
        Actor->SetSpeed(-10, 10);
        while (Gyro->yaw() > Angle - 90)
        {
            FPlatformProcess::Sleep(0.1);
        }
    }
    Actor->SetSpeed(0, 0);
}

void UDriver::go()
{
    sptr<ILasers> Lasers = RobotServiceLocator::instance().sl()->getContext()->resolve<ILasers>();
    sptr<IGyro> Gyro = RobotServiceLocator::instance().sl()->getContext()->resolve<IGyro>();
    float Start = Lasers->readF();
    float Angle = Gyro->yaw();
    if (Start < 30.0) return;
    Actor->SetSpeed(100, 100);
    while (Lasers->readF() > Start - 30)
    {
        float CurrentYaw = Gyro->yaw();
        float DeltaYaw = (180 - abs(abs(Angle - CurrentYaw) - 180));
        if (Angle > CurrentYaw) DeltaYaw *= -1;
        Actor->SetSpeed(80 - DeltaYaw * 10, 80 + DeltaYaw * 10);
        FPlatformProcess::Sleep(0.1);
    }
    Actor->SetSpeed(0, 0);
}
