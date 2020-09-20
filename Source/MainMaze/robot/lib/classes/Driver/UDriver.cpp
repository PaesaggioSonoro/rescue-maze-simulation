#include "UDriver.hpp"

#include "MainMaze/robot/lib/interfaces/ILasers.hh"
#include "MainMaze/robot/servicelocator/RobotServiceLocator.hpp"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

UDriver::UDriver(DrivableActor* DrivableActor) : Actor(DrivableActor)
{
}

void UDriver::rotate(bool right)
{
    float Angle = Actor->GetActor()->GetActorRotation().Yaw;
    if (right)
    {
        Actor->SetSpeed(50, -49);
        while (Actor->GetActor()->GetActorRotation().Yaw < Angle + 80)
        {
            FPlatformProcess::Sleep(0.1);
        }
        Actor->SetSpeed(10, -9);
        while (Actor->GetActor()->GetActorRotation().Yaw < Angle + 90)
        {
            FPlatformProcess::Sleep(0.1);
        }
    }
    else
    {
        Actor->SetSpeed(-49, 50);
        while (Actor->GetActor()->GetActorRotation().Yaw > Angle - 80)
        {
            FPlatformProcess::Sleep(0.1);
        }
        Actor->SetSpeed(-9, 10);
        while (Actor->GetActor()->GetActorRotation().Yaw > Angle - 90)
        {
            FPlatformProcess::Sleep(0.1);
        }
    }
    Actor->SetSpeed(0, 0);
}

void UDriver::go()
{
    sptr<ILasers> Lasers = RobotServiceLocator::instance().sl()->getContext()->resolve<ILasers>();
    float Start = Lasers->readF();
    if (Start < 30.0) return;
    Actor->SetSpeed(80, 80);
    while (Lasers->readF() > Start - 30)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green,
                                         FString::Printf(TEXT("Distance: %f"), Lasers->readF()));

        FPlatformProcess::Sleep(0.1);
    }
    Actor->SetSpeed(0, 0);
}
