// Fill out your copyright notice in the Description page of Project Settings.

#include "ThreadClass.h"


#include "MainMaze/robot/Robot.h"
#include "MainMaze/robot/lib/interfaces/IBus.h"
#include "robot/servicelocator/RobotServiceLocator.h"


ThreadClass::ThreadClass(int val, DrivableActor* Actor)
{
    this->UpLimit = val;
    this->Actor = Actor;
}

void ThreadClass::DoWork()
{
    auto& rsl = RobotServiceLocator::instance();
    rsl.sl()->getContext()->resolve<IBus>()->SetBus(Actor);
    Robot().setup();
    for (int32 i = 1; i <= this->UpLimit; i++)
    {
        bool isPrime = true;

        for (int32 j = 2; j <= i / 2; j++)
        {
            if (FMath::Fmod(i, j) == 0)
            {
                isPrime = false;
                break;
            }
        }

        if (isPrime)
            GLog->Log("Prime number #" + FString::FromInt(i) + ": " + FString::FromInt(i));
    }
    GLog->Log("--------------------------------------------------------------------");
    GLog->Log("End of prime numbers calculation on game thread");
    GLog->Log("--------------------------------------------------------------------");
}
