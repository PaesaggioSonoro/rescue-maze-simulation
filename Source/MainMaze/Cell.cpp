// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"

#include "Wall.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACell::ACell()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    UStaticMeshComponent* BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
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

void ACell::Build(std::vector<int> walls, UMaterialInterface* material, std::vector<int> temps, bool black, bool checkpoint)
{

    this->black_ = black;
    this->checkpoint_ = checkpoint;

    Cast<UStaticMeshComponent>(RootComponent)->SetMaterial(0, material);

    for (int i = 0; i < walls.size(); i++) // access by reference to avoid copying
    {
        if (walls[i] == 1)
        {
            FVector location = GetActorLocation();
            location.X += points_[i][0];
            location.Y += points_[i][1];
            FTransform transform = FTransform(location);
            transform.SetRotation(FRotator(0, -90 * (i + 1), 0).Quaternion());
            AWall* wall = GetWorld()->SpawnActorDeferred<AWall>(AWall::StaticClass(), transform);
            wall->temp = temps[i] ? 40 : 25;
            UGameplayStatics::FinishSpawningActor(wall, wall->GetTransform());
        }
    }
}

bool ACell::IsBlack() const
{
    return black_;
}

bool ACell::IsCheckpoint() const
{
    return checkpoint_;
}
