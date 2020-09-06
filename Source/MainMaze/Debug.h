// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Gyro.h"
#include "MLX90614.h"

#include "UObject/UObjectGlobals.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Debug.generated.h"



UCLASS()
class MAINMAZE_API ADebug : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebug();

	//MAIN
	UPROPERTY(EditAnywhere, Category = "Main", meta = (DisplayName = "Main Character"))
	AActor* Robot;

	/*UPROPERTY(EditAnywhere, Category = "Main", meta = (DisplayName = "Multi-threading"))
	bool multithreading;*/


	//GYRO
	//Log
	UPROPERTY(EditAnywhere, Category = "Gyro|Log", meta = (DisplayName = "Enable logging"))
	bool GyroDebug = false;
	UPROPERTY(EditAnywhere, Category = "Gyro|Log|Axis", meta = (EditCondition = "GyroDebug", DisplayName = "Show Yaw"))
	bool ShowYaw = true;
	UPROPERTY(EditAnywhere, Category = "Gyro|Log|Axis", meta = (EditCondition = "GyroDebug", DisplayName = "Show Roll"))
	bool ShowRoll = true;
	UPROPERTY(EditAnywhere, Category = "Gyro|Log|Axis", meta = (EditCondition = "GyroDebug", DisplayName = "Show Pitch"))
	bool ShowPitch = true;
	//Errors
	UPROPERTY(EditAnywhere, Category = "Gyro|Errors", DisplayName = "Generate error")
	bool Errore = true;
	UPROPERTY(EditAnywhere, Category = "Gyro|Errors", meta = (EditCondition="Errore",ClampMin = "-10", ClampMax = "10", UIMin = "0", UIMax = "2"), DisplayName = "Drift Multiplier")
	float Drift = 1.0;
	UPROPERTY(EditAnywhere, Category = "Gyro|Errors", meta = (EditCondition = "Errore"))
	bool Calibrate;

	//THERMOMETER
	//Log
	UPROPERTY(EditAnywhere, Category = "Thermometer", meta = (DisplayName = "Enable logging"))
	bool ThermDebug = false;

	Gyro imu;
	MLX90614 therm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
