// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"    //AActor
#include <cstdlib>                  //random
#include <ctime>                    //random seed
#include <chrono>

using namespace std::chrono;


class MAINMAZE_API IMU
{
public:
    IMU();
    void begin(AActor* TMainCharacter);
    bool checko();
    void start(unsigned long refresh);
    float yaw();
    float roll();
    float pitch();
    //float getTemperature();
    void calibrate();



    //Unreal Private
    float drift = 1;
    bool error = true;
    

private:
    AActor* MainCharacter;
    float CalculateError();

    float max_error = 0.0;

};
/*
class IMU {
public:
    IMU() : microsPerReading(0) {}
    void begin();
    bool check();
    void start(unsigned long refresh);
    float yaw();
    float roll();
    float pitch();
    float getTemperature();
    void calibrate();
    void update();
private:
    void read();
    MPU6050 imu;
    Madgwick filter;
    unsigned long microsPerReading;
    unsigned long microsPrevious;
}
*/