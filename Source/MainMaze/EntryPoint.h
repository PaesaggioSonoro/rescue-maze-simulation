// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Json.h"
#include "EntryPoint.generated.h"

using namespace std;

UCLASS()
class MAINMAZE_API AEntryPoint : public AActor
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, Category = "Main")
    bool ShowIntro = true;
    UPROPERTY(EditAnywhere, Category = "Main|Class", meta = (DisplayName = "Cell to spawn"))
    TSubclassOf<AActor> CellToSpawn;
    UPROPERTY(EditAnywhere, Category = "Main|Class", meta = (DisplayName = "Wall to spawn"))
    TSubclassOf<AActor> WallToSpawn;
    UPROPERTY(EditAnywhere, Category = "Main|Class")
    AActor* MainVehicle;
    UPROPERTY(EditAnywhere, Category = "Main|Class")
    AActor* CameraActor;
    


    UPROPERTY(EditAnywhere, Category = "Main|Materials")
    class UMaterialInterface* BlackMaterial;
    UPROPERTY(EditAnywhere, Category = "Main|Materials")
    class UMaterialInterface* CheckpointMaterial;
    UPROPERTY(EditAnywhere, Category = "Main|Materials")
    class UMaterialInterface* BaseMaterial;

    /**Enabling this option allows to start level directly from here, but the JSON file is not selectable */
    UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayName = "Fast start"))
    bool fast_start = true;

    UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayName="Level number", ClampMin = "0", ClampMax = "15",
        UIMin = "0", UIMax = "3"))
    int level_n = 0;

public:
    // Sets default values for this actor's properties
    AEntryPoint();

    UFUNCTION(BlueprintCallable, Category="Introduction")
    bool GetShowIntro() const;

    UFUNCTION(BlueprintCallable, Category="Robot")
    void StartRobot() const;


protected:
    // Called when the game starts or when spawned
    void BeginPlay() override;

public:
    // Called every frame
    void Tick(float DeltaTime) override;

private:
    TSharedPtr<FJsonObject> JsonData;
    const int DISTANCE = 30;
    const int HEIGHT = 0;
};
