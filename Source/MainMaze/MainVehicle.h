// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#define _USE_MATH_DEFINES
#define WHEEL_CIRC 168.075206967
#define MAX_SPEED 173.677713866

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "Point.h"
//#include "ThreadClass.h"

#include <math.h>
#include <string.h>

#include "DrivableActor.h"
#include "GameFramework/Actor.h"
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
	int speed_R;
	UPROPERTY(EditAnywhere, Category="Speed", meta = (ClampMin = "-255", ClampMax = "255", UIMin = "-15", UIMax = "15"))
	int speed_L;

	/*UFUNCTION(BlueprintCallable, Category = "MotorSpeed")
	static void SetSpeedLeft(const int delta);
	UFUNCTION(BlueprintCallable, Category = "MotorSpeed")
	static void SetSpeedRight(const int delta);
	UFUNCTION(BlueprintCallable, Category = "MotorDebug")
	static FString GetSpeed();*/

	void brake();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FRotator GetRotator() override;
	
	virtual void SetSpeedR(int speed) override;
	virtual void SetSpeedL(int speed) override;
	virtual void SetSpeed(int speedL, int speedR) override;

private:

	float height;
	const float D = 100.0;	// distanza tra ruote
	const float R = 50.0;	// D/2
	const float TO_DEGREES = 180 / M_PI;

	float getDistance(int speed, float time);
	float getRadius(float l1, float l2);
	float getAngle(float l1, float l2, float r);

	void move(float time);

};
