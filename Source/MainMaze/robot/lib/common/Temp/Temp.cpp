#include "Temp.hpp"


#if _EXECUTION_ENVIRONMENT == 0

void Temp::Calibrate()
{
	const GeometricPair<float> values = Read();
	threshold = (values.left + values.right) / 2;
}

GeometricPair<float> Temp::Read() const
{
	const auto out = GeometricPair<float>(
		ReadSide(GetBus()->GetActor()->GetActorRightVector() * -1),
		ReadSide(GetBus()->GetActor()->GetActorRightVector())
	);
	return out;
}

GeometricPair<bool> Temp::IsHot() const
{
	const auto measures = Read();
	return GeometricPair<bool>(
		measures.left > threshold,
		measures.right > threshold
	);
}

float Temp::ReadSide(FVector direction) const
{
	FHitResult out_hit;

	FVector start = GetBus()->GetActor()->GetActorLocation();

	FVector end = start + direction * 1000.0f;

	FCollisionQueryParams collision_params;

	bool is_hit = GetBus()->GetActor()->GetWorld()->LineTraceSingleByChannel(out_hit, start, end, ECC_Visibility,
	                                                                         collision_params);
	float result = 0;
	if (is_hit)
	{
		AWall* wall = Cast<AWall>(out_hit.GetActor());
		if (wall) result = wall->temp;
		// if (wall) result = (OutHit.Distance < 30) ? wall->temp : 25;
	}
	return result;
}
#endif
