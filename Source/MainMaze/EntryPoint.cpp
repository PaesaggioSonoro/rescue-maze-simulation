// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryPoint.h"

// Sets default values
AEntryPoint::AEntryPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UE_LOG(LogTemp, Warning, TEXT("dsafda: %s"), UPathContainer::getPath());
	if (fast_start==true) {
#if _DEBUG_MACHINE == 0
		std::ifstream in(R"(C:\Users\Stark\Documents\Unreal Projects\MainMaze\Source\MainMaze\default.json)");
#else
		std::ifstream in(R"(F:\Unreal Projects\MainMaze\Source\MainMaze\default.json)");
#endif
		//std::ifstream in(TEXT("default.json"));
		std::string file((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
		data.Parse(file.c_str());
	}
	else {
		std::ifstream in(UPathContainer::getPath());
		std::string file((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());
		data.Parse(file.c_str());
	}

	

}

// Called when the game starts or when spawned
void AEntryPoint::BeginPlay()
{
	Super::BeginPlay();
	const Value& dims = data["header"]["dims"];
	// int d_x = (dims[0].GetInt()) * DISTANCE, d_y = (dims[1].GetInt()) * DISTANCE;
	FVector location = GetActorLocation();
	float bias_x = location.X, bias_y = location.Y, bias_z = location.Z;


	const Value& level = data["body"][level_n];
	for (unsigned int i = 0; i < level.GetArray().Capacity(); i++) {
		FVector newPos = FVector(DISTANCE * level[i]["coord"][0].GetInt() + bias_x, DISTANCE * level[i]["coord"][1].GetInt() + bias_y, HEIGHT + bias_z);
		FTransform newTr = FTransform(newPos);
		std::vector<int> v;
		for (auto& val : level[i]["walls"].GetArray()) {
			v.push_back(val.GetInt());
		}
		ACell* a = GetWorld()->SpawnActorDeferred<ACell>(CellToSpawn, newTr);

		UMaterialInterface* material;

		if (level[i]["black"].GetBool()) {
			material = BlackMaterial;
		}
		else if (level[i]["checkpoint"].GetBool()) {
			material = CheckpointMaterial;
		}
		else {
			material = BaseMaterial;
		}

		a->Build(*WallToSpawn, v, material);
		UGameplayStatics::FinishSpawningActor(a, a->GetTransform());
	}

	FVector StartLocation = FVector((data["header"]["start"][1].GetInt() * DISTANCE + bias_x) + DISTANCE/2.0, (data["header"]["start"][2].GetInt() * DISTANCE + bias_y) + DISTANCE/2.0, HEIGHT*2 + bias_z);
	FRotator StartRotation = FRotator(0, 0, 0);
	CameraActor->SetActorLocationAndRotation(StartLocation, StartRotation, false, 0, ETeleportType::None);

	APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);
	MyController->SetViewTargetWithBlend(CameraActor, 2.f);
}

// Called every frame
void AEntryPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

