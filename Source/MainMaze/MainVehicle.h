// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define _USE_MATH_DEFINES
#define WHEEL_CIRC 168.075206967
#define MAX_SPEED 173.677713866

#include "CoreMinimal.h"
#include "Point.h"
#include "DrivableActor.h"
#include "MainVehicle.generated.h"

UCLASS()
class MAINMAZE_API AMainVehicle : public AActor, public DrivableActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMainVehicle();

    UPROPERTY(EditAnywhere, Category = "Debug")
    bool EnableDebug = false;

    UPROPERTY(EditAnywhere, Category = "Debug")
    bool UseThread = false;

    UPROPERTY(EditAnywhere, Category = "Debug")
    int UpperLimit = 100000;

    UPROPERTY(EditAnywhere, Category="Speed", meta = (ClampMin = "-255", ClampMax = "255", UIMin = "-15", UIMax = "15"))
    int Speed_R;
    UPROPERTY(EditAnywhere, Category="Speed", meta = (ClampMin = "-255", ClampMax = "255", UIMin = "-15", UIMax = "15"))
    int Speed_L;

    void Brake();

protected:
    // Called when the game starts or when spawned
    void BeginPlay() override;

public:
    // Called every frame
    void Tick(float DeltaTime) override;

    AActor* GetActor() override;

    FVector GetSize() const override;

    void SetSpeedR(int Speed) override;
    void SetSpeedL(int Speed) override;
    void SetSpeed(int SpeedL, int SpeedR) override;

private:

    float Height;
    const FVector Size = FVector(20, 15, 12);
    const float D = Size.Y; // distanza tra ruote
    const float R = Size.Y / 2; // D/2
    const float TO_DEGREES = 180 / M_PI;

    float GetDistance(int Speed, float Time);
    float GetRadius(float L1, float L2);
    float GetAngle(float L1, float L2, float Radius);

    void Move(float Time);
};
