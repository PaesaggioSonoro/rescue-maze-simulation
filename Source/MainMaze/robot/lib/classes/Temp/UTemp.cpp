#include "UTemp.hpp"

#include "DrawDebugHelpers.h"
#include "MainMaze/Wall.h"


UTemp::UTemp(DrivableActor* DrivableActor) : Actor(DrivableActor)
{
}

void UTemp::calibrate()
{
    GeometricPair<float> values = read();
    threshold = (values.left + values.right) / 2;
}

GeometricPair<float> UTemp::read()
{
    auto out = GeometricPair<float>(
        ReadSide(Actor->GetActor()->GetActorRightVector() * -1),
        ReadSide(Actor->GetActor()->GetActorRightVector())
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

float UTemp::ReadSide(FVector Direction)
{
    FHitResult OutHit;

    FVector Start = Actor->GetActor()->GetActorLocation();

    FVector End = (Start + (Direction * 1000.0f));

    FCollisionQueryParams CollisionParams;

    bool isHit = Actor->GetActor()->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility,
                                                                         CollisionParams);
    float result = 0;
    if (isHit)
    {
        AWall* Wall = Cast<AWall>(OutHit.GetActor());
        if (Wall) result = Wall->temp;
        // if (wall) result = (OutHit.Distance < 30) ? wall->temp : 25;
    }
    return result;
}
