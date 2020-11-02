// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "DrivableActor.h"

/**
 * 
 */
class MAINMAZE_API ThreadClass : public FNonAbandonableTask
{
    DrivableActor* Actor;

public:
    ThreadClass(DrivableActor* Actor);

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(ThreadClass, STATGROUP_ThreadPoolAsyncTasks);
    }

    void DoWork();

    void RunRobot() const;

    ~ThreadClass();
};
