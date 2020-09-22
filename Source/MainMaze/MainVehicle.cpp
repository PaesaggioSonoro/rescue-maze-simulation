// Fill out your copyright notice in the Description page of Project Settings.


#include "MainVehicle.h"

#include "DrawDebugHelpers.h"

// Sets default values
AMainVehicle::AMainVehicle()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

void AMainVehicle::Brake()
{
    Speed_L = 0;
    Speed_R = 0;
}

// Called when the game starts or when spawned
void AMainVehicle::BeginPlay()
{
    Super::BeginPlay();
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

void AMainVehicle::SetSpeedR(int Speed)
{
    this->Speed_R = Speed + CalculateError();
}

void AMainVehicle::SetSpeedL(int Speed)
{
    this->Speed_L = Speed + CalculateError();
}

void AMainVehicle::SetSpeed(int SpeedL, int SpeedR)
{
    this->SetSpeedL(SpeedL);
    this->SetSpeedR(SpeedR);
}

float AMainVehicle::GetDistance(int Speed, float Time)
{
    return ((Speed * MAX_SPEED) / 255.0) * Time;
}

float AMainVehicle::GetRadius(float L1, float L2)
{
    if (L1 == L2) return -R;
    return (-L1 * D) / (L1 - L2); // L1 / r = L2 / (r + D) 
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
    float L1 = GetDistance(Speed_R, Time); // First Arch (rightmost)
    float L2 = GetDistance(Speed_L, Time); // Second Arch (leftmost)
    float Radius = GetRadius(L1, L2); // Radius (referring to right)
    float Angle = GetAngle(L1, L2, Radius); // Absolute Angle
    Radius += R; // Make Radius referring to Center
    float x = GetActorLocation().X, y = GetActorLocation().Y, z = GetActorLocation().Z;

    FRotator Rotator = GetActorRotation();
    Point Pivot, Center;

    if (Radius == 0.0) // Moving forward or rotating in place
    {
        Pivot = Point(x, y);
        Center = Point(x + (L1 + L2) / 2.0, y);
        Center.rotate(Pivot, GetActorRotation().Yaw);
    }
    else
    {
        Pivot = Point(x, y + Radius);
        Center = Point(x, y);
        Pivot.rotate(Center, GetActorRotation().Yaw);
        Center.rotate(Pivot, Angle);
    }
    Rotator.Yaw += Angle;


    if (EnableDebug)
    {
        UE_LOG(LogTemp, Warning, TEXT("delta time: %f"), Time);
        UE_LOG(LogTemp, Warning, TEXT("speed_L %d, speed_R: %d, l1: %f, l2: %f, radius: %f, angle: %f"), Speed_L,
               Speed_R, L1, L2, Radius, Angle);

        DrawDebugPoint(GetWorld(), FVector(Center.x, Center.y, Height), 2, FColor::Blue, false, 8.f);
        DrawDebugPoint(GetWorld(), FVector(Pivot.x, Pivot.y, Height), 10, FColor::Red, false, 2.f);
        Point lw = Point(x, y - R);
        Point rw = Point(x, y + R);
        lw.rotate(Point(x, y), GetActorRotation().Yaw);
        rw.rotate(Point(x, y), GetActorRotation().Yaw);
        DrawDebugPoint(GetWorld(), FVector(lw.x, lw.y, Height), 2, FColor::Green, false, 20.f);
        DrawDebugPoint(GetWorld(), FVector(rw.x, rw.y, Height), 2, FColor::Green, false, 20.f);

        UE_LOG(LogTemp, Warning, TEXT("pos: %f, %f, %f"), x, y, z);

        UE_LOG(LogTemp, Warning, TEXT("pivot: %f, %f"), Pivot.x, Pivot.y);

        UE_LOG(LogTemp, Warning, TEXT("center: %f, %f"), Center.x, Center.y);
    }

    FVector location = Center.toVector(Height);
    SetActorLocationAndRotation(location, Rotator, false, nullptr, ETeleportType::None);
}
