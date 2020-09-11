#include "UTemp.hpp"

#include "DrawDebugHelpers.h"
#include "MainMaze/Wall.h"


UTemp::UTemp(DrivableActor* actor)
{
    this->actor = actor;
}

void UTemp::calibrate()
{
    GeometricPair<float> values = read();
    threshold = (values.left + values.right) / 2;
}

GeometricPair<float> UTemp::read()
{
    auto out = GeometricPair<float>(
        readSide(actor->GetActor()->GetActorRightVector().MirrorByVector(FVector::RightVector)),
        readSide(actor->GetActor()->GetActorRightVector())
    );
    return out;
}

GeometricPair<bool> UTemp::isHot()
{
    auto measures = read();
    return GeometricPair<bool>(
        measures.left > threshold,
        measures.right > threshold
    );
}

float UTemp::readSide(FVector direction)
{
    FHitResult OutHit;

    FVector Start = actor->GetActor()->GetActorLocation();

    FVector End = (Start + (direction * 1000.0f));

    FCollisionQueryParams CollisionParams;

    bool isHit = actor->GetActor()->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility,
                                                                         CollisionParams);
    float result = 0;
    if (isHit)
    {
        AWall* wall = Cast<AWall>(OutHit.GetActor());
        if (wall) result = wall->temp;
        // if (wall) result = (OutHit.Distance < 30) ? wall->temp : 25;
    }
    return result;
}
