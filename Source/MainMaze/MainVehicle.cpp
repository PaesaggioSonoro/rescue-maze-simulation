// Fill out your copyright notice in the Description page of Project Settings.


#include "MainVehicle.h"

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

void AMainVehicle::brake()
{
    speed_L = 0;
    speed_R = 0;
}

// Called when the game starts or when spawned
void AMainVehicle::BeginPlay()
{
    Super::BeginPlay();
    //if (UseThread) (new FAutoDeleteAsyncTask<ThreadClass>(UpperLimit, this))->StartBackgroundTask();
    height = GetActorLocation().Z;
}

// Called every frame
void AMainVehicle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    move(DeltaTime);
}

FRotator AMainVehicle::GetRotator()
{
    return this->GetActorRotation();
}

void AMainVehicle::SetSpeedR(int speed)
{
    this->speed_R = speed;
}

void AMainVehicle::SetSpeedL(int speed)
{
    this->speed_L = speed;
}

void AMainVehicle::SetSpeed(int speedL, int speedR)
{
    this->speed_L = speedL;
    this->speed_R = speedR;
}

float AMainVehicle::getDistance(int speed, float time)
{
    return ((speed * MAX_SPEED) / 255.0) * time;
}

float AMainVehicle::getRadius(float l1, float l2)
{
    if (l1 == l2) return -R;
    return (-l1 * D) / (l1 - l2);
}

float AMainVehicle::getAngle(float l1, float l2, float r)
{
    if (r == 0 && l1 != 0) return 0.0;
    float radians;
    if (l1 != 0) radians = l1 / r;
    else radians = l2 / (r + D);
    return radians * TO_DEGREES;
}

void AMainVehicle::move(float time)
{
    float l1 = getDistance(speed_R, time);
    float l2 = getDistance(speed_L, time);
    float radius = getRadius(l1, l2);
    float angle = getAngle(l1, l2, radius);
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
        UE_LOG(LogTemp, Warning, TEXT("delta time: %f"), time);
        UE_LOG(LogTemp, Warning, TEXT("speed_L %d, speed_R: %d, l1: %f, l2: %f, radius: %f, angle: %f"), speed_L,
               speed_R, l1, l2, radius, angle);

        DrawDebugPoint(GetWorld(), FVector(center.x, center.y, height), 2, FColor::Blue, false, 8.f);
        DrawDebugPoint(GetWorld(), FVector(pivot.x, pivot.y, height), 10, FColor::Red, false, 2.f);
        Point lw = Point(x, y - R);
        Point rw = Point(x, y + R);
        lw.rotate(Point(x, y), GetActorRotation().Yaw);
        rw.rotate(Point(x, y), GetActorRotation().Yaw);
        DrawDebugPoint(GetWorld(), FVector(lw.x, lw.y, height), 2, FColor::Green, false, 20.f);
        DrawDebugPoint(GetWorld(), FVector(rw.x, rw.y, height), 2, FColor::Green, false, 20.f);

        UE_LOG(LogTemp, Warning, TEXT("pos: %f, %f, %f"), x, y, z);

        UE_LOG(LogTemp, Warning, TEXT("pivot: %f, %f"), pivot.x, pivot.y);

        UE_LOG(LogTemp, Warning, TEXT("center: %f, %f"), center.x, center.y);
    }

    FVector location = center.toVector(height);
    SetActorLocationAndRotation(location, rotator, false, 0, ETeleportType::None);
}
