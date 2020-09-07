// Fill out your copyright notice in the Description page of Project Settings.

#include "ThreadClass.h"


ThreadClass::ThreadClass(int val)
{
    this->UpLimit = val;
}

void ThreadClass::DoWork()
{
    (new Robot())->setup();
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
