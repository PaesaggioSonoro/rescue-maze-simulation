// Fill out your copyright notice in the Description page of Project Settings.

#include "ThreadClass.h"


#include "MainMaze/robot/Robot.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "robot/servicelocator/RobotServiceLocator.hpp"
#include "Core/Public/Windows/AllowWindowsPlatformTypes.h"
#include "Windows.h"
#include "Core/Public/Windows/HideWindowsPlatformTypes.h"


ThreadClass::ThreadClass(DrivableActor* Actor)
{
    this->Actor = Actor;
}

void ThreadClass::DoWork()
{
    auto& rsl = RobotServiceLocator::instance();
    rsl.sl()->getContext()->resolve<IBus>()->setBus(Actor);
    RunRobot();
}

void ThreadClass::RunRobot() const
{
    __try
    {
        Robot().setup();
    }
    __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION)
    {
        UE_LOG(LogTemp, Error, TEXT("EXCEPTION_ACCESS_VIOLATION, QUITTING..."));
    }
}

ThreadClass::~ThreadClass()
{
    UE_LOG(LogTemp, Error, TEXT("CLOSING THREAD"));
}
