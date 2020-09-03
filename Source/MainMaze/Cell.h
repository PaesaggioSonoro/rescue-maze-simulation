// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
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
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Build(TSubclassOf<AActor> Wall, std::vector<int> walls, UMaterialInterface* material);

private:
	int points[4][2] = { {30, 30}, {30, 0}, {0, 0}, {0, 30} };
	class UStaticMeshComponent* BaseMesh;

};
