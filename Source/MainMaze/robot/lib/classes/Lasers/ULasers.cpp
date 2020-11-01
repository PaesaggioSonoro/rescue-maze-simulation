#include "ULasers.hpp"


#include "DrawDebugHelpers.h"
#include "MainMaze/robot/utils/Constants.hxx"


ULasers::ULasers(DrivableActor* DrivableActor) : Actor(DrivableActor)
{
}

float ULasers::readF()
{
    return Read(Actor->GetActor()->GetActorForwardVector()) - Dimensions::DEPTH / 2;
}

float ULasers::computeFrontAngle()
{
    return sqrt(pow(readFL() - readFR(), 2) + pow(Dimensions::FRONT_LASERS_DISTANCE, 2));
}

float ULasers::readFL()
{
    return Read(Actor->GetActor()->GetActorForwardVector(), -Dimensions::FRONT_LASERS_DISTANCE / 2)
        - Dimensions::DEPTH / 2;
}

float ULasers::readFR()
{
    return Read(Actor->GetActor()->GetActorForwardVector(), Dimensions::FRONT_LASERS_DISTANCE / 2)
        - Dimensions::DEPTH / 2;
}

float ULasers::readL()
{
    return Read(Actor->GetActor()->GetActorRightVector() * -1)
        - Dimensions::WIDTH / 2;
}

float ULasers::readR()
{
    return Read(Actor->GetActor()->GetActorRightVector())
        - Dimensions::WIDTH / 2;
}

float ULasers::readB()
{
    return Read(Actor->GetActor()->GetActorForwardVector() * -1)
        - Dimensions::DEPTH / 2;
}

float ULasers::Read(FVector Direction, float DeltaY)
{
    FHitResult OutHit;

    FVector Start = Actor->GetActor()->GetActorLocation();
    if (DeltaY != 0) Start += Actor->GetActor()->GetActorRotation().RotateVector(FVector(0, DeltaY, 0));

    FVector End = (Start + (Direction * 800.0f));

    FCollisionQueryParams CollisionParams;

    bool isHit = Actor->GetActor()->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility,
                                                                         CollisionParams);

    DrawDebugLine(Actor->GetActor()->GetWorld(), Start, FVector(OutHit.Location), FColor::Blue, false, 0.5, 0, 0.5);
    float result = pow(2, 13);
    if (isHit)
    {
        result = OutHit.Distance;
    }
    return result;
}
