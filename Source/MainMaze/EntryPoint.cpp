// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryPoint.h"

#include <fstream>
#include <vector>


#include "Cell.h"
#include "MainVehicle.h"
#include "PathManager.h"
#include "ThreadClass.h"

// Sets default values
AEntryPoint::AEntryPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FString FullPath;

	if (fast_start)
		FullPath = FPaths::ProjectContentDir() + R"(Maps\default2.json)";
	else
		FullPath = FString(UPathManager::GetPath().c_str());

	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);
	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

	if (!FJsonSerializer::Deserialize(JsonReader, JsonData))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red,
		                                 FString::Printf(TEXT("Error Loading Json")));
	}
}

// Called when the game starts or when spawned
void AEntryPoint::BeginPlay()
{
	Super::BeginPlay();
	const FVector Location = GetActorLocation();
	const float Bias_X = Location.X, Bias_Y = Location.Y, Bias_Z = Location.Z;


	const TArray<TSharedPtr<FJsonValue>> Level = JsonData->GetArrayField("body")[level_n]->AsArray();
	for (int i = 0; i < Level.Num(); i++)
	{
		const auto& JsonCell = Level[i]->AsObject();

		const auto& Coord = JsonCell->GetArrayField("coord");
		FVector NewPos = FVector(DISTANCE * Coord[0]->AsNumber() + Bias_X,
		                         DISTANCE * Coord[1]->AsNumber() + Bias_Y, HEIGHT + Bias_Z);
		FTransform NewTr = FTransform(NewPos);

		std::vector<int> Walls;
		for (auto& Val : JsonCell->GetArrayField("walls"))
		{
			Walls.push_back(Val->AsNumber());
		}

		std::vector<int> Temps;
		for (auto& Val : JsonCell->GetArrayField("victims"))
		{
			Temps.push_back(Val->AsNumber());
		}

		ACell* a = GetWorld()->SpawnActorDeferred<ACell>(CellToSpawn, NewTr);

		UMaterialInterface* Material;
		const bool black = JsonCell->GetBoolField("black"), checkpoint = JsonCell->GetBoolField("checkpoint");

		if (black)
		{
			Material = BlackMaterial;
		}
		else if (checkpoint)
		{
			Material = CheckpointMaterial;
		}
		else
		{
			Material = BaseMaterial;
		}

		a->Build(Walls, Material, Temps, black, checkpoint);
		UGameplayStatics::FinishSpawningActor(a, a->GetTransform());
	}

	const auto& Start = JsonData->GetObjectField("header")->GetArrayField("start");
	const FVector StartLocation = FVector(
		(Start[1]->AsNumber() * DISTANCE + Bias_X) + DISTANCE / 2.0,
		(Start[2]->AsNumber() * DISTANCE + Bias_Y) + DISTANCE / 2.0,
		(HEIGHT + Bias_Z + 15));
	const FRotator StartRotation = FRotator(0, 90, 0);
	MainVehicle->SetActorLocationAndRotation(StartLocation, StartRotation, false, nullptr, ETeleportType::None);

	APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);

	
	//MyController->SetViewTargetWithBlend(CameraActor, 2.f);
	MyController->SetViewTarget(CameraActor);

}

// Called every frame
void AEntryPoint::Tick(float DeltaTime) // DISABLED
{
	Super::Tick(DeltaTime);
}

bool AEntryPoint::GetShowIntro() const { return ShowIntro; }

void AEntryPoint::StartRobot() const
{
	DrivableActor* Actor = Cast<AMainVehicle>(MainVehicle);
	if (Actor != nullptr)
	{
		FAutoDeleteAsyncTask<ThreadClass>* task = new FAutoDeleteAsyncTask<ThreadClass>(Actor);
		task->StartBackgroundTask();
	}
}
