#include "Driver.hpp"


#if _EXECUTION_ENVIRONMENT == 0

void Driver::rotate(bool right)
{
	bool bDebug = false;
	Gyro* Gyro = Gyro::instance();
	Lasers* Lasers = Lasers::instance();
	const int DirectionMultiplier = right ? 1 : -1;

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
	Goal = FRotator::ClampAxis(Start + 88 * DirectionMultiplier);
	getBus()->SetSpeed(10 * DirectionMultiplier, -10 * DirectionMultiplier);
	while (right ? RightTurnCondition(Start, Current, Goal) : LeftTurnCondition(Start, Current, Goal))
	{
		FPlatformProcess::Sleep(0.001);
		Current = Gyro->yaw();
	}
	getBus()->SetSpeed(0, 0);
}

void Driver::go()
{
	Lasers* Lasers = Lasers::instance();
	float CurrentDistance = Lasers->readF();
	const int MissingCells = static_cast<int>(CurrentDistance) / static_cast<int>(CellDimensions::DEPTH);
	const float Objective = (MissingCells - 1) * CellDimensions::DEPTH + (CellDimensions::DEPTH - Dimensions::DEPTH) /
		2;
	int Speed;
	while (CurrentDistance > Objective)
	{
		float DeltaYaw = 0;
		const float Lateral = Lasers->computeLateralDifference();
		const float FrontC = Lasers->readF(), FrontR = Lasers->readFR(), FrontL = Lasers->readFL();
		const bool bNear = FrontC < Objective + 5, bValid = Lasers::isValidWall(FrontL, FrontC, FrontR);

		if (bValid)
		{
			DeltaYaw += Lasers::frontDifference(FrontL, FrontR) * FRONTAL_COMPENSATION_MULTIPLIER;
			Speed = bNear ? 50 : 100;
		}
		else
		{
			DeltaYaw += abs(FrontR - FrontC) < abs(FrontL - FrontC) ? 12 : -12;
			Speed = 5;
		}

		if (Lateral < LATERAL_COMPENSATION_THRESHOLD && Lateral > -LATERAL_COMPENSATION_THRESHOLD)
		{
			DeltaYaw += FMath::Clamp(Lateral * LATERAL_COMPENSATION_MULTIPLIER, -MAX_LATERAL_COMPENSATION_SPEED,
			                         MAX_LATERAL_COMPENSATION_SPEED);
		}
		UE_LOG(LogTemp, Warning, TEXT("objective: %f, missingcells: %d, distance: %f, speed: %d, deltayaw: %f"),
		       Objective, MissingCells, CurrentDistance, Speed, DeltaYaw);
		getBus()->SetSpeed(Speed - DeltaYaw, Speed + DeltaYaw);
		FPlatformProcess::Sleep(bNear ? 0.01 : 0.2);
		if (bValid) CurrentDistance = Lasers->readF();
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
