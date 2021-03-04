#include "Driver.hpp"

#include "MainMaze/robot/data/Directions.hxx"


#if _EXECUTION_ENVIRONMENT == 0

void Driver::rotate(const bool right)
{
	Gyro* gyro = Gyro::instance();
	Lasers* Lasers = Lasers::instance();
	int DirectionMultiplier = right ? 1 : -1;
	float c = Lasers->readF(), r = Lasers->readFR(), l = Lasers->readFL();

	if (Lasers::isValidWall(l, c, r))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid wall, centralizing"));
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
	}


	const float Start = gyro->yaw();
	float Goal = FRotator::ClampAxis(Start + 85 * DirectionMultiplier);
	float Current = Start;


	while (right ? RightTurnCondition(Start, Current, Goal) : LeftTurnCondition(Start, Current, Goal))
	{
		FPlatformProcess::Sleep(0.1);
		Current = gyro->yaw();
		UE_LOG(LogTemp, Warning, TEXT("MAIN -> starting: %f, objective: %f, current: %f"), Start, Goal, Current);
	}
	c = Lasers->readF(), r = Lasers->readFR(), l = Lasers->readFL();
	getBus()->SetSpeed(10 * DirectionMultiplier, -10 * DirectionMultiplier);
	float diff = Lasers->computeFrontDifference();
	if (Lasers::isValidWall(l, c, r))
	{
		while (right ? diff < 0 : diff > 0)
		{
			FPlatformProcess::Sleep(0.001);
			diff = Lasers->computeFrontDifference();
			UE_LOG(LogTemp, Warning, TEXT("FINAL -> difference: %f"), diff);
		}
	}
	else
	{
		Goal = FRotator::ClampAxis(Start + 90 * DirectionMultiplier);
		while (right ? RightTurnCondition(Start, Current, Goal) : LeftTurnCondition(Start, Current, Goal))
		{
			FPlatformProcess::Sleep(0.001);
			Current = gyro->yaw();
			UE_LOG(LogTemp, Warning, TEXT("FINAL -> starting: %f, objective: %f, current: %f"), Start, Goal, Current);
		}
	}
	getBus()->SetSpeed(0, 0);
}

void Driver::go()
{
	Lasers* Lasers = Lasers::instance();
	Gyro* Gyro = Gyro::instance();

	const float FrontDistance = Lasers->readF(), BackDistance = Lasers->readB();
	const float StartRotation = Gyro->yaw();
	const bool UseFront = FrontDistance < BackDistance;
	float CurrentDistance = UseFront ? FrontDistance : BackDistance;
	const int Cells = static_cast<int>(CurrentDistance) / static_cast<int>(CellDimensions::DEPTH);
	const float Objective = std::max(
		5.f, (Cells + (UseFront ? -1 : 1)) * CellDimensions::DEPTH + (CellDimensions::DEPTH -
			Dimensions::DEPTH) / 2);
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

		float CurrentAngle = Gyro->yaw();
		float DeltaAngle = CurrentAngle - StartRotation;
		if (DeltaAngle > 180) DeltaAngle -= 360;
		else if (DeltaAngle < -180) DeltaAngle += 360;

		if (abs(DeltaAngle) > DEGREE_OVERRIDE_THRESHOLD)
		{
			Speed = Slow;
			compensating = true;
			DeltaYaw = STUCK_COMPENSATION_MULTIPLIER * (DeltaAngle > 0 ? 1 : -1);
		}
		else if (isValidWall)
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
			       "objective: %f, missingcells: %d, distance: %f, speed: %d, deltayaw: %f, dc: %f, laser: %hs, compensating: %d"
		       ),
		       Objective, Cells, CurrentDistance, Speed, DeltaYaw, DistanceComponent, UseFront?"front":"back",
		       compensating);
		UE_LOG(LogTemp, Warning, TEXT("direction: %d, startangle: %f, currentangle: %f, anglediff: %f"), isValidWall,
		       StartRotation, CurrentAngle, DeltaAngle);
		getBus()->SetSpeed(Speed - DeltaYaw, Speed + DeltaYaw);
		FPlatformProcess::Sleep(bNear ? 0.01 : 0.2);
		if (isValidWall) CurrentDistance = UseFront ? Lasers->readF() : Lasers->readB();
	}
	getBus()->SetSpeed(0, 0);
}

bool Driver::RightTurnCondition(const float start, const float current, const float goal)
{
	if (goal >= start)
	{
		return start <= current && current <= goal;
	}
	return start <= current && current <= 360 || 0 <= current && current <= goal;
}

bool Driver::LeftTurnCondition(const float start, const float current, const float goal)
{
	if (goal < start)
	{
		return goal <= current && current <= start;
	}
	return 0 <= current && current <= start || goal <= current && current <= 360;
}
#endif
