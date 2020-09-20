#include "ULasers.hpp"


#include "DrawDebugHelpers.h"
#include "MainMaze/robot/utils/Constants.hxx"


ULasers::ULasers(DrivableActor* DrivableActor) : Actor(DrivableActor)
{
}

float ULasers::readF()
{
    return Read(Actor->GetActor()->GetActorForwardVector(), 0) - Dimensions::depth / 2;
}

float ULasers::computeFrontAngle()
{
    return sqrt(pow(readFL() - readFR(), 2) + pow(Dimensions::frontLasersDistance, 2));
}

float ULasers::readFL()
{
    return Read(Actor->GetActor()->GetActorForwardVector(), -Dimensions::frontLasersDistance / 2)
        - Dimensions::depth / 2;
}

float ULasers::readFR()
{
    return Read(Actor->GetActor()->GetActorForwardVector(), Dimensions::frontLasersDistance / 2)
        - Dimensions::depth / 2;
}

float ULasers::readL()
{
    return Read(Actor->GetActor()->GetActorRightVector().MirrorByVector(FVector::RightVector), 0)
        - Dimensions::width / 2;
}

float ULasers::readR()
{
    return Read(Actor->GetActor()->GetActorRightVector(), 0)
        - Dimensions::width / 2;
}

float ULasers::readB()
{
    return Read(Actor->GetActor()->GetActorForwardVector().MirrorByVector(FVector::ForwardVector), 0)
        - Dimensions::depth / 2;
}

float ULasers::Read(FVector Direction, float DeltaY)
{
    FHitResult OutHit;

    FVector Start = Actor->GetActor()->GetActorLocation();
    Start.Y += DeltaY;
    // Start = Actor->GetActor()->GetActorRotation().RotateVector(Start);

    FVector End = (Start + (Direction * 1000.0f));

    FCollisionQueryParams CollisionParams;

    bool isHit = Actor->GetActor()->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility,
                                                                         CollisionParams);
    float result = pow(2, 13);
    if (isHit)
    {
        result = OutHit.Distance;
    }
    return result;
}
