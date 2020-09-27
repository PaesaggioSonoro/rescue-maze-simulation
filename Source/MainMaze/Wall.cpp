// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"

// Sets default values
AWall::AWall()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    UStaticMeshComponent*  BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
    RootComponent = BaseMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh>
        BaseAsset(TEXT("/Game/Cell/Assets/Wall_SM.Wall_SM"));
    if (BaseAsset.Succeeded())
    {
        BaseMesh->SetStaticMesh(BaseAsset.Object);
        BaseMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        BaseMesh->SetWorldScale3D(FVector(1.f));
        BaseMesh->SetRelativeScale3D(FVector());
        static ConstructorHelpers::FObjectFinder<UMaterialInterface> BaseMaterial(
            TEXT(
                "/Game/Megascans/Surfaces/Concrete_Wall_2x2_M_00/Concrete_Wall_2x2_M_00_inst.Concrete_Wall_2x2_M_00_inst"));
        if (BaseMaterial.Succeeded())
        {
            BaseMesh->SetMaterial(0, BaseMaterial.Object);
        }
    }
}


// Called when the game starts or when spawned
void AWall::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
