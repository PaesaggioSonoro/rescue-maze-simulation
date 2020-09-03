// Fill out your copyright notice in the Description page of Project Settings.


#include "IMU.h"

//string IMU::path;

IMU::IMU() 
{

}

void IMU::begin(AActor* TMainCharacter)
{
    MainCharacter = TMainCharacter;

}

bool IMU::checko() { return true; }

void IMU::start(unsigned long refresh) {}

float IMU::yaw()
{
    return MainCharacter->GetActorRotation().Yaw + CalculateError();
}

float IMU::roll()
{
    return MainCharacter->GetActorRotation().Roll + CalculateError();
}

float IMU::pitch()
{
    return MainCharacter->GetActorRotation().Pitch + CalculateError();
}

void IMU::calibrate()
{
    max_error = 0.0;
}

float IMU::CalculateError()
{
    if (error)
    {
        srand((int)time(0));
        auto now = high_resolution_clock::now();
        auto nanos = duration_cast<nanoseconds>(now.time_since_epoch()).count();
        srand(nanos);
        max_error += ((rand() % 100) - 50) / (500.0 * (1/drift));

        return max_error;
    }
    else 
    { 
        return 0.0; 
    }
    
}

/*
IMU() : microsPerReading(0) {}
    void begin();
    bool check();
    void start(unsigned long refresh);
    float yaw();
    float roll();
    float pitch();
    */