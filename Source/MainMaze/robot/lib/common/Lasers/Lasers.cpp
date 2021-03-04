#include "Lasers.hpp"

#include <utility>


#if _EXECUTION_ENVIRONMENT == 0

float Lasers::ReadF() const
{
	return Read(GetBus()->GetActor()->GetActorForwardVector()) - dimensions::depth / 2;
}

float Lasers::ComputeFrontAngle() const
{
	return -atan((ReadFl() - ReadFr()) / dimensions::front_lasers_distance);
}

float Lasers::ComputeFrontDifference() const
{
	return ReadFr() - ReadFl();
}

float Lasers::ComputeLateralDifference() const
{
	return fmod(ReadL(), cell_dimensions::depth) - fmod(ReadR(), cell_dimensions::depth);
}

float Lasers::ReadFl() const
{
	return Read(GetBus()->GetActor()->GetActorForwardVector(), -dimensions::front_lasers_distance / 2)
		- dimensions::depth / 2;
}

float Lasers::ReadFr() const
{
	return Read(GetBus()->GetActor()->GetActorForwardVector(), dimensions::front_lasers_distance / 2)
		- dimensions::depth / 2;
}

float Lasers::ReadL() const
{
	return Read(GetBus()->GetActor()->GetActorRightVector() * -1)
		- dimensions::width / 2;
}

float Lasers::ReadR() const
{
	return Read(GetBus()->GetActor()->GetActorRightVector())
		- dimensions::width / 2;
}

float Lasers::ReadB() const
{
	return Read(GetBus()->GetActor()->GetActorForwardVector() * -1)
		- dimensions::depth / 2;
}

bool Lasers::IsValidWall(const float l, const float c, const float r, const int tolerance)
{
	const float mean = std::min(r, l) + abs(r - l) / 2;
	return abs(l - r) < dimensions::front_lasers_distance && mean - tolerance <= c && c <= mean + tolerance;
}

float Lasers::FrontDifference(const float l, const float r)
{
	return r - l;
}

float Lasers::Read(FVector direction, float delta_y, bool draw) const
{
	FHitResult out_hit;

	FVector start = GetBus()->GetActor()->GetActorLocation();
	if (delta_y != 0) start += GetBus()->GetActor()->GetActorRotation().RotateVector(FVector(0, delta_y, 0));

	FVector end = (start + (direction * 800.0f));

	FCollisionQueryParams collision_params;

	bool is_hit = GetBus()->GetActor()->GetWorld()->LineTraceSingleByChannel(out_hit, start, end, ECC_Visibility,
	                                                                        collision_params);

	if (draw)
		DrawDebugLine(GetBus()->GetActor()->GetWorld(), start, FVector(out_hit.Location), FColor::Blue, false, 0.5,
		              0, 0.5);
	float result = 8192;
	if (is_hit)
	{
		result = out_hit.Distance;
	}
	return MakeError(result);
}

float Lasers::MakeError(const float value) const
{
	return value * FMath::RandRange(0.97f, 1.03f);
}
#endif
