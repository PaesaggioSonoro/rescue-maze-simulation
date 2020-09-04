// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/UObjectGlobals.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PathContainer.h"
#include <fstream>
#include <string.h>
#include <vector>
#include "Cell.h"
#include "rapidjson/document.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntryPoint.generated.h"

using namespace rapidjson;
using namespace std;

UCLASS()
class MAINMAZE_API AEntryPoint : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Main|Class", meta = (DisplayName = "Cell to spawn"))
	TSubclassOf<AActor> CellToSpawn;
	UPROPERTY(EditAnywhere, Category = "Main|Class", meta = (DisplayName = "Wall to spawn"))
	TSubclassOf<AActor> WallToSpawn;
	UPROPERTY(EditAnywhere, Category = "Main|Class")
	AActor* CameraActor;

	UPROPERTY(EditAnywhere, Category = "Main|Materials")
	class UMaterialInterface* BlackMaterial;
	UPROPERTY(EditAnywhere, Category = "Main|Materials")
	class UMaterialInterface* CheckpointMaterial;
	UPROPERTY(EditAnywhere, Category = "Main|Materials")
	class UMaterialInterface* BaseMaterial;

	/**Enabling this option allows to start level directly from here, but the JSON file is not choosable. */
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayName = "Fast start"))
	bool fast_start = true;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayName="Level number", ClampMin = "0", ClampMax = "15", UIMin = "0", UIMax = "3"))
	int level_n = 0;

	

	

	
	
public:	
	// Sets default values for this actor's properties
	AEntryPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	Document data;
	const int DISTANCE = 30;
	const int HEIGHT = 100;

};
