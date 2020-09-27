#include "UDriver.hpp"


#include "MainMaze/robot/lib/interfaces/IGyro.hh"
#include "MainMaze/robot/lib/interfaces/ILasers.hh"
#include "MainMaze/robot/servicelocator/RobotServiceLocator.hpp"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"
#include "Math/UnrealMathUtility.h"

UDriver::UDriver(DrivableActor* DrivableActor) : Actor(DrivableActor)
{
}

void UDriver::rotate(bool right)
{
    bool bDebug = false;
    sptr<IGyro> Gyro = RobotServiceLocator::instance().sl()->getContext()->resolve<IGyro>();
    float Start = Gyro->yaw();
    if (right)
    {
        float Goal = FRotator::ClampAxis(Start + 80);
        Actor->SetSpeed(50, -50);
        if (bDebug)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
                                             FString::Printf(TEXT("Goal Angle: %f"), Goal));
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
                                             FString::Printf(TEXT("Start Angle: %f"), Start));
        }
        float Current = Start;
        while (RightTurnCondition(Start, Current, Goal))
        {
            FPlatformProcess::Sleep(0.1);
            Current = Gyro->yaw();
        }
        Goal = FRotator::ClampAxis(Start + 88);
        Actor->SetSpeed(10, -10);
        while (RightTurnCondition(Start, Current, Goal))
        {
            if (bDebug)
                GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
                                                 FString::Printf(TEXT("Curent Angle: %f"), Current));
            FPlatformProcess::Sleep(0.001);
            Current = Gyro->yaw();
        }
    }
    else
    {
        float Goal = FRotator::ClampAxis(Start - 80);
        Actor->SetSpeed(-50, 50);
        if (bDebug)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
                                             FString::Printf(TEXT("Goal Angle: %f"), Goal));
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
                                             FString::Printf(TEXT("Start Angle: %f"), Start));
        }
        float Current = Start;
        while (LeftTurnCondition(Start, Current, Goal))
        {
            FPlatformProcess::Sleep(0.1);
            Current = Gyro->yaw();
        }
        Goal = FRotator::ClampAxis(Start - 88);
        Actor->SetSpeed(-10, 10);
        while (LeftTurnCondition(Start, Current, Goal))
        {
            if (bDebug)
                GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
                                                 FString::Printf(TEXT("Current Angle: %f"), Current));
            FPlatformProcess::Sleep(0.001);
            Current = Gyro->yaw();
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
        float DeltaYaw = FMath::FindDeltaAngleRadians(CurrentYaw, Angle);
        if (Angle > CurrentYaw) DeltaYaw *= -1;
        GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
                                         FString::Printf(TEXT("DeltaYaw: %f"), DeltaYaw));
        Actor->SetSpeed(80 - DeltaYaw , 80 + DeltaYaw );
        FPlatformProcess::Sleep(0.1);
    }
    Actor->SetSpeed(0, 0);
}

bool UDriver::RightTurnCondition(const float Start, const float Current, const float Goal)
{
    if (Goal >= Start)
    {
        return Start <= Current && Current <= Goal;
    }
    return Start <= Current && Current <= 360 || 0 <= Current && Current <= Goal;
}

bool UDriver::LeftTurnCondition(const float Start, const float Current, const float Goal)
{
    if (Goal < Start)
    {
        return Goal <= Current && Current <= Start;
    }
    return 0 <= Current && Current <= Start || Goal <= Current && Current <= 360;
}
