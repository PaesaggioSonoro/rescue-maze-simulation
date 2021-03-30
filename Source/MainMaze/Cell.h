// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/Actor.h"
#include "Cell.generated.h"

using namespace std;

UCLASS()
class MAINMAZE_API ACell : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACell();

protected:
    // Called when the game starts or when spawned
    void BeginPlay() override;


public:
    // Called every frame
    void Tick(float DeltaTime) override;
    void Build(std::vector<int> walls, UMaterialInterface* material, std::vector<int> temps, bool black, bool checkpoint);
    bool IsBlack() const;
    bool IsCheckpoint() const;

private:
    int points_[4][2] = {{30, 30}, {30, 0}, {0, 0}, {0, 30}};
    bool black_ = false;
    bool checkpoint_ = false;
};
