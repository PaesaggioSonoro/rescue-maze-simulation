#include "Temp.hpp"


#if _EXECUTION_ENVIRONMENT == 0

void Temp::calibrate()
{
	GeometricPair<float> values = read();
	threshold = (values.left + values.right) / 2;
}

GeometricPair<float> Temp::read()
{
	auto out = GeometricPair<float>(
		ReadSide(getBus()->GetActor()->GetActorRightVector() * -1),
		ReadSide(getBus()->GetActor()->GetActorRightVector())
	);
	return out;
}

GeometricPair<bool> Temp::isHot()
{
	auto measures = read();
	return GeometricPair<bool>(
		measures.left > threshold,
		measures.right > threshold
	);
}

float Temp::ReadSide(FVector Direction)
{
	FHitResult OutHit;

	FVector Start = getBus()->GetActor()->GetActorLocation();

	FVector End = (Start + (Direction * 1000.0f));

	FCollisionQueryParams CollisionParams;

	bool isHit = getBus()->GetActor()->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility,
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
#endif
