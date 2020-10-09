// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug.h"



// Sets default values
ADebug::ADebug()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    //Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
    Box1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX1"));
}

// Called when the game starts or when spawned
void ADebug::BeginPlay()
{
    Super::BeginPlay();
    // imu.begin(Robot);
    // therm.begin(Robot);

    
    //Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ADebug::OnOverlapBegin);
    Box1->OnComponentBeginOverlap.AddDynamic(this, &ADebug::OnOverlapBegin);

}
void ADebug::OnOverlapBegin(class UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PICKED UP!")));
}


// Called every frame
void ADebug::Tick(float DeltaTime)
{

    
    Super::Tick(DeltaTime);
    /*GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Yaw: %f"), imu.yaw()));
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Error: %f"), imu.max_error));*/
    //
    // if (Calibrate)
    // {
    // 	Calibrate = false;
    // 	imu.calibrate();
    // }
    // imu.drift = Drift;
    // imu.error = Errore;
    //
    // if (GyroDebug)
    // {
    // 	
    // 	if (ShowYaw)
    // 	{
    // 		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Yaw: %f"), imu.yaw()));
    // 	}
    // 	if (ShowRoll)
    // 	{
    // 		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Roll: %f"), imu.roll()));
    // 	}
    // 	if (ShowPitch)
    // 	{
    // 		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Pitch: %f"), imu.pitch()));
    // 	}
    // }
    // if (ThermDebug)
    // {
    // 	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Temperature: %f"), therm.read()));
    // }
    //
    //
}
