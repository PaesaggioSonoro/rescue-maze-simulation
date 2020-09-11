// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"

#include "Wall.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACell::ACell()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    RootComponent = BaseMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseAsset(TEXT("/Game/Cell/Assets/Floor_BSP.Floor_BSP"));
    if (BaseAsset.Succeeded())
    {
        BaseMesh->SetStaticMesh(BaseAsset.Object);
        BaseMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        BaseMesh->SetWorldScale3D(FVector(1.f));
    }
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACell::Build(std::vector<int> walls, UMaterialInterface* material, bool temp)
{
    BaseMesh->SetMaterial(0, material);

    for (int i = 0; i < walls.size(); i++) // access by reference to avoid copying
    {
        if (walls[i] == 1)
        {
            FVector location = GetActorLocation();
            location.X += points[i][0];
            location.Y += points[i][1];
            FTransform Transform = FTransform(location);
            Transform.SetRotation(FRotator(0, -90 * (i + 1), 0).Quaternion());
            AWall* wall = GetWorld()->SpawnActorDeferred<AWall>(AWall::StaticClass(), Transform);
            wall->temp = temp ? 40 : 25;
            UGameplayStatics::FinishSpawningActor(wall, wall->GetTransform());
        }
    }
}
