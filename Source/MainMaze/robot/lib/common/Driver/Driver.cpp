#include "Driver.hpp"


#if _EXECUTION_ENVIRONMENT == 0

void Driver::rotate(bool right)
{
	Gyro* Gyro = Gyro::instance();
	Lasers* Lasers = Lasers::instance();
	int DirectionMultiplier = right ? 1 : -1;

	if (right)
	{
		getBus()->SetSpeed(-20, 20);
		while (Lasers->computeFrontDifference() > 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
		getBus()->SetSpeed(50, -50);
		while (Lasers->computeFrontDifference() < 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
	}
	else
	{
		getBus()->SetSpeed(20, -20);
		while (Lasers->computeFrontDifference() < 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
		getBus()->SetSpeed(-50, 50);
		while (Lasers->computeFrontDifference() > 1) FPlatformProcess::Sleep(0.01); // Align with the front wall
	}

	float Start = Gyro->yaw();
	float Goal = FRotator::ClampAxis(Start + 80 * DirectionMultiplier);
	float Current = Start;
	while (right ? RightTurnCondition(Start, Current, Goal) : LeftTurnCondition(Start, Current, Goal))
	{
		FPlatformProcess::Sleep(0.1);
		Current = Gyro->yaw();
	}
	Goal = FRotator::ClampAxis(Start + 90 * DirectionMultiplier);
	getBus()->SetSpeed(10 * DirectionMultiplier, -10 * DirectionMultiplier);
	while (right ? RightTurnCondition(Start, Current, Goal) : LeftTurnCondition(Start, Current, Goal))
	{
		FPlatformProcess::Sleep(0.001);
		Current = Gyro->yaw();
	}

	const float FrontC = Lasers->readF(), FrontR = Lasers->readFR(), FrontL = Lasers->readFL();
	if (!Lasers::isValidWall(FrontL, FrontC, FrontR))
	{
		DirectionMultiplier = abs(FrontR - FrontC) < abs(FrontL - FrontC) ? -1 : 1;
		getBus()->SetSpeed(-10 * DirectionMultiplier, 10 * DirectionMultiplier);
		while (!Lasers->isValidWall(Lasers->readFL(), Lasers->readF(), Lasers->readFR())) FPlatformProcess::Sleep(0.01);
	}
	getBus()->SetSpeed(0, 0);
}

void Driver::go()
{
	Lasers* Lasers = Lasers::instance();
	const float FrontDistance = Lasers->readF(), BackDistance = Lasers->readB();
	const bool UseFront = FrontDistance < BackDistance;
	float CurrentDistance = UseFront ? FrontDistance : BackDistance;
	const float StartDistance = CurrentDistance;
	const int Cells = static_cast<int>(CurrentDistance) / static_cast<int>(CellDimensions::DEPTH);
	const float Objective = (Cells + (UseFront ? -1 : 1)) * CellDimensions::DEPTH + (CellDimensions::DEPTH -
		Dimensions::DEPTH) / 2;
	int Speed;
	float DeltaYaw = 0;
	bool compensating = false;
	while (UseFront ? CurrentDistance > Objective : CurrentDistance < Objective)
	{
		const float c = Lasers->readF(), r = Lasers->readFR(), l = Lasers->readFL();
		const float Lateral = Lasers->computeLateralDifference();
		const bool bNear = c < Objective + 5;
		float DistanceComponent = std::max(1.f, CurrentDistance / CellDimensions::DEPTH);

		bool isValidWall = Lasers::isValidWall(l, c, r);

		if (isValidWall)
		{
			compensating = false;
			DeltaYaw = Lasers::frontDifference(l, r) * FRONTAL_COMPENSATION_MULTIPLIER;
			Speed = bNear ? Medium : Fast;
			DeltaYaw /= DistanceComponent;
			if (Lateral < LATERAL_COMPENSATION_THRESHOLD && Lateral > -LATERAL_COMPENSATION_THRESHOLD)
			{
				DeltaYaw += FMath::Clamp(Lateral * LATERAL_COMPENSATION_MULTIPLIER, -MAX_LATERAL_COMPENSATION_SPEED,
				                         MAX_LATERAL_COMPENSATION_SPEED);
			}
		}
		else
		{
			Speed = Medium;
			if (!compensating)
			{
				compensating = true;
				DeltaYaw = STUCK_COMPENSATION_MULTIPLIER * (DeltaYaw > 0 ? -1 : 1);
			}
		}


		UE_LOG(LogTemp, Warning,
		       TEXT(
			       "objective: %f, missingcells: %d, distance: %f, speed: %d, deltayaw: %f, dc: %f, direction: %d, laser: %hs"
		       ),
		       Objective, Cells, CurrentDistance, Speed, DeltaYaw, DistanceComponent, isValidWall,
		       UseFront?"front":"back");
		getBus()->SetSpeed(Speed - DeltaYaw, Speed + DeltaYaw);
		FPlatformProcess::Sleep(bNear ? 0.01 : 0.2);
		if (isValidWall) CurrentDistance = UseFront ? Lasers->readF() : Lasers->readB();
	}
	getBus()->SetSpeed(0, 0);
}

bool Driver::RightTurnCondition(const float Start, const float Current, const float Goal)
{
	if (Goal >= Start)
	{
		return Start <= Current && Current <= Goal;
	}
	return Start <= Current && Current <= 360 || 0 <= Current && Current <= Goal;
}

bool Driver::LeftTurnCondition(const float Start, const float Current, const float Goal)
{
	if (Goal < Start)
	{
		return Goal <= Current && Current <= Start;
	}
	return 0 <= Current && Current <= Start || Goal <= Current && Current <= 360;
}
#endif
