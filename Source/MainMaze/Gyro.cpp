// Fill out your copyright notice in the Description page of Project Settings.


#include "Gyro.h"

//string Gyro::path;

Gyro::Gyro() 
{

}

void Gyro::begin(AActor* TMainCharacter)
{
    MainCharacter = TMainCharacter;

}

bool Gyro::checko() { return true; }

void Gyro::start(unsigned long refresh) {}

float Gyro::yaw()
{
    return MainCharacter->GetActorRotation().Yaw + CalculateError();
}

float Gyro::roll()
{
    return MainCharacter->GetActorRotation().Roll + CalculateError();
}

float Gyro::pitch()
{
    return MainCharacter->GetActorRotation().Pitch + CalculateError();
}

void Gyro::calibrate()
{
    max_error = 0.0;
}

float Gyro::CalculateError()
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
Gyro() : microsPerReading(0) {}
    void begin();
    bool check();
    void start(unsigned long refresh);
    float yaw();
    float roll();
    float pitch();
    */