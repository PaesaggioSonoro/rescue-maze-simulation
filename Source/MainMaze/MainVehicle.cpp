// Fill out your copyright notice in the Description page of Project Settings.


#include "MainVehicle.h"

#include "DrawDebugHelpers.h"

// Fill out your copyright notice in the Description page of Project Settings.

/*int AMainVehicle::speed_R = 255;
int AMainVehicle::speed_L = 255;*/

// Sets default values
AMainVehicle::AMainVehicle()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

/*void AMainVehicle::SetSpeedLeft(const int delta)
{
	speed_L += delta;
}

void AMainVehicle::SetSpeedRight(const int delta)
{
	speed_R += delta;
}

FString AMainVehicle::GetSpeed()
{
	return FString::Printf(TEXT("L: %d    R: %d"), speed_L, speed_R);
}*/

void AMainVehicle::Brake()
{
    Speed_L = 0;
    Speed_R = 0;
}

// Called when the game starts or when spawned
void AMainVehicle::BeginPlay()
{
    Super::BeginPlay();
    //if (UseThread) (new FAutoDeleteAsyncTask<ThreadClass>(UpperLimit, this))->StartBackgroundTask();
    Height = GetActorLocation().Z;
}

// Called every frame
void AMainVehicle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Move(DeltaTime);
}

AActor* AMainVehicle::GetActor()
{
    return Cast<AActor>(this);
}

FVector AMainVehicle::GetSize() const
{
    return Size;
}

void AMainVehicle::SetSpeedR(int Speed)
{
    this->Speed_R = Speed;
}

void AMainVehicle::SetSpeedL(int Speed)
{
    this->Speed_L = Speed;
}

void AMainVehicle::SetSpeed(int SpeedL, int SpeedR)
{
    this->Speed_L = SpeedL;
    this->Speed_R = SpeedR;
}

float AMainVehicle::GetDistance(int Speed, float Time)
{
    return ((Speed * MAX_SPEED) / 255.0) * Time;
}

float AMainVehicle::GetRadius(float L1, float L2)
{
    if (L1 == L2) return -R;
    return (-L1 * D) / (L1 - L2);
}

float AMainVehicle::GetAngle(float L1, float L2, float Radius)
{
    if (Radius == 0 && L1 != 0) return 0.0;
    float radians;
    if (L1 != 0) radians = L1 / Radius;
    else radians = L2 / (Radius + D);
    return radians * TO_DEGREES;
}

void AMainVehicle::Move(float Time)
{
    float l1 = GetDistance(Speed_R, Time);
    float l2 = GetDistance(Speed_L, Time);
    float radius = GetRadius(l1, l2);
    float angle = GetAngle(l1, l2, radius);
    radius += R;
    float x = GetActorLocation().X, y = GetActorLocation().Y, z = GetActorLocation().Z;

    FRotator rotator = GetActorRotation();


    Point pivot, center;

    if (radius == 0.0)
    {
        pivot = Point(x, y);
        center = Point(x + l1, y);
        center.rotate(pivot, GetActorRotation().Yaw);
    }
    else
    {
        pivot = Point(x, y + radius);
        center = Point(x, y);
        pivot.rotate(center, GetActorRotation().Yaw);
        center.rotate(pivot, angle);
        rotator.Yaw += angle;
    }


    if (EnableDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("delta time: %f"), Time);
        UE_LOG(LogTemp, Warning, TEXT("speed_L %d, speed_R: %d, l1: %f, l2: %f, radius: %f, angle: %f"), Speed_L,
               Speed_R, l1, l2, radius, angle);

        DrawDebugPoint(GetWorld(), FVector(center.x, center.y, Height), 2, FColor::Blue, false, 8.f);
        DrawDebugPoint(GetWorld(), FVector(pivot.x, pivot.y, Height), 10, FColor::Red, false, 2.f);
        Point lw = Point(x, y - R);
        Point rw = Point(x, y + R);
        lw.rotate(Point(x, y), GetActorRotation().Yaw);
        rw.rotate(Point(x, y), GetActorRotation().Yaw);
        DrawDebugPoint(GetWorld(), FVector(lw.x, lw.y, Height), 2, FColor::Green, false, 20.f);
        DrawDebugPoint(GetWorld(), FVector(rw.x, rw.y, Height), 2, FColor::Green, false, 20.f);

        UE_LOG(LogTemp, Warning, TEXT("pos: %f, %f, %f"), x, y, z);

        UE_LOG(LogTemp, Warning, TEXT("pivot: %f, %f"), pivot.x, pivot.y);

        UE_LOG(LogTemp, Warning, TEXT("center: %f, %f"), center.x, center.y);
    }

    FVector location = center.toVector(Height);
    SetActorLocationAndRotation(location, rotator, false, nullptr, ETeleportType::None);
}
