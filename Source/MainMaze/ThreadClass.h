// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "robot/Robot.h"
#include "CoreMinimal.h"

/**
 * 
 */
class MAINMAZE_API ThreadClass : public FNonAbandonableTask
{
    int UpLimit;

public:
    ThreadClass(int val);

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(ThreadClass, STATGROUP_ThreadPoolAsyncTasks);
    }

    void DoWork();
};
