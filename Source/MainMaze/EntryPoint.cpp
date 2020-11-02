// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryPoint.h"

#include <fstream>


#include "Cell.h"
#include "MainVehicle.h"
#include "PathManager.h"
#include "ThreadClass.h"

// Sets default values
AEntryPoint::AEntryPoint()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    if (fast_start)
    {
#if _DEBUG_MACHINE == 0
        std::ifstream In(R"(C:\Users\Stark\Documents\Unreal Projects\MainMaze\Source\MainMaze\default.json)");
#else
		std::ifstream In(R"(F:\Unreal Projects\MainMaze\Source\MainMaze\default.json)");
#endif
        std::string file((std::istreambuf_iterator<char>(In)),
                         std::istreambuf_iterator<char>());
        Data.Parse(file.c_str());
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
                                         FString::Printf(TEXT("Path: %hs"), UPathManager::GetPath().c_str()));
        std::ifstream in(UPathManager::GetPath());
        std::string file((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());
        Data.Parse(file.c_str());
    }
}

// Called when the game starts or when spawned
void AEntryPoint::BeginPlay()
{
    Super::BeginPlay();
    const FVector Location = GetActorLocation();
    const float Bias_X = Location.X, Bias_Y = Location.Y, Bias_Z = Location.Z;


    const Value& Level = Data["body"][level_n];
    for (unsigned int i = 0; i < Level.GetArray().Capacity(); i++)
    {
        FVector NewPos = FVector(DISTANCE * Level[i]["coord"][0].GetInt() + Bias_X,
                                 DISTANCE * Level[i]["coord"][1].GetInt() + Bias_Y, HEIGHT + Bias_Z);
        FTransform NewTr = FTransform(NewPos);
        std::vector<int> Walls;
        for (auto& Val : Level[i]["walls"].GetArray())
        {
            Walls.push_back(Val.GetInt());
        }
        std::vector<int> Temps;
        for (auto& Val : Level[i]["victims"].GetArray())
        {
            Temps.push_back(Val.GetInt());
        }
        ACell* a = GetWorld()->SpawnActorDeferred<ACell>(CellToSpawn, NewTr);

        UMaterialInterface* Material;

        if (Level[i]["black"].GetBool())
        {
            Material = BlackMaterial;
        }
        else if (Level[i]["checkpoint"].GetBool())
        {
            Material = CheckpointMaterial;
        }
        else
        {
            Material = BaseMaterial;
        }

        a->Build(Walls, Material, Temps);
        UGameplayStatics::FinishSpawningActor(a, a->GetTransform());
    }

    const FVector StartLocation = FVector((Data["header"]["start"][1].GetInt() * DISTANCE + Bias_X) + DISTANCE / 2.0,
                                          (Data["header"]["start"][2].GetInt() * DISTANCE + Bias_Y) + DISTANCE / 2.0,
                                          (HEIGHT + Bias_Z + 15));
    const FRotator StartRotation = FRotator(0, 0, 0);
    CameraActor->SetActorLocationAndRotation(StartLocation, StartRotation, false, nullptr, ETeleportType::None);

    APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);
    MyController->SetViewTargetWithBlend(CameraActor, 2.f);
}

// Called every frame
void AEntryPoint::Tick(float DeltaTime) // DISABLED
{
    Super::Tick(DeltaTime);
}

bool AEntryPoint::GetShowIntro() const { return ShowIntro; }

void AEntryPoint::StartRobot() const
{
    DrivableActor* Actor = Cast<AMainVehicle>(CameraActor);
    if (Actor != nullptr)
    {
        FAutoDeleteAsyncTask<ThreadClass>* task = new FAutoDeleteAsyncTask<ThreadClass>(Actor);
        task->StartBackgroundTask();
    }
}
