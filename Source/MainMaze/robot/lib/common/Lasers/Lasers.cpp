#include "Lasers.hpp"




#if _EXECUTION_ENVIRONMENT == 0

float Lasers::readF()
{
	return Read(getBus()->GetActor()->GetActorForwardVector()) - Dimensions::DEPTH / 2;
}

float Lasers::computeFrontAngle()
{
	return sqrt(pow(readFL() - readFR(), 2) + pow(Dimensions::FRONT_LASERS_DISTANCE, 2));
}

float Lasers::readFL()
{
	return Read(getBus()->GetActor()->GetActorForwardVector(), -Dimensions::FRONT_LASERS_DISTANCE / 2)
		- Dimensions::DEPTH / 2;
}

float Lasers::readFR()
{
	return Read(getBus()->GetActor()->GetActorForwardVector(), Dimensions::FRONT_LASERS_DISTANCE / 2)
		- Dimensions::DEPTH / 2;
}

float Lasers::readL()
{
	return Read(getBus()->GetActor()->GetActorRightVector() * -1)
		- Dimensions::WIDTH / 2;
}

float Lasers::readR()
{
	return Read(getBus()->GetActor()->GetActorRightVector())
		- Dimensions::WIDTH / 2;
}

float Lasers::readB()
{
	return Read(getBus()->GetActor()->GetActorForwardVector() * -1)
		- Dimensions::DEPTH / 2;
}

float Lasers::Read(FVector Direction, float DeltaY)
{
	FHitResult OutHit;

	FVector Start = getBus()->GetActor()->GetActorLocation();
	if (DeltaY != 0) Start += getBus()->GetActor()->GetActorRotation().RotateVector(FVector(0, DeltaY, 0));

	FVector End = (Start + (Direction * 800.0f));

	FCollisionQueryParams CollisionParams;

	bool isHit = getBus()->GetActor()->GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility,
	                                                                        CollisionParams);

	DrawDebugLine(getBus()->GetActor()->GetWorld(), Start, FVector(OutHit.Location), FColor::Blue, false, 0.5, 0, 0.5);
	float result = pow(2, 13);
	if (isHit)
	{
		result = OutHit.Distance;
	}
	return result;
}
#endif
