#include "Driver.hpp"


#if _EXECUTION_ENVIRONMENT == 0

void Driver::rotate(bool right)
{
	bool bDebug = false;
	Gyro* Gyro = Gyro::instance();
	Lasers* Lasers = Lasers::instance();
	if (right)
	{
		getBus()->SetSpeed(-20, 20);
		while (Lasers->computeFrontDifference() > 0) FPlatformProcess::Sleep(0.01); // Align with the front wall
		getBus()->SetSpeed(50, -50);
		while (Lasers->computeFrontDifference() < 0) FPlatformProcess::Sleep(0.01); // Align with the front wall

		float Start = Gyro->yaw();
		float Goal = FRotator::ClampAxis(Start + 80);
		if (bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
			                                 FString::Printf(TEXT("Goal Angle: %f"), Goal));
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
			                                 FString::Printf(TEXT("Start Angle: %f"), Start));
		}
		float Current = Start;
		while (RightTurnCondition(Start, Current, Goal))
		{
			FPlatformProcess::Sleep(0.1);
			Current = Gyro->yaw();
		}
		Goal = FRotator::ClampAxis(Start + 88);
		getBus()->SetSpeed(10, -10);
		while (RightTurnCondition(Start, Current, Goal))
		{
			if (bDebug)
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
				                                 FString::Printf(TEXT("Curent Angle: %f"), Current));
			FPlatformProcess::Sleep(0.001);
			Current = Gyro->yaw();
		}
	}
	else
	{
		getBus()->SetSpeed(20, -20);
		while (Lasers->computeFrontDifference() < 0) FPlatformProcess::Sleep(0.01); // Align with the front wall
		getBus()->SetSpeed(-50, 50);
		while (Lasers->computeFrontDifference() > 0) FPlatformProcess::Sleep(0.01); // Align with the front wall

		float Start = Gyro->yaw();
		float Goal = FRotator::ClampAxis(Start - 80);
		if (bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
			                                 FString::Printf(TEXT("Goal Angle: %f"), Goal));
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
			                                 FString::Printf(TEXT("Start Angle: %f"), Start));
		}
		float Current = Start;
		while (LeftTurnCondition(Start, Current, Goal))
		{
			FPlatformProcess::Sleep(0.1);
			Current = Gyro->yaw();
		}
		Goal = FRotator::ClampAxis(Start - 88);
		getBus()->SetSpeed(-10, 10);
		while (LeftTurnCondition(Start, Current, Goal))
		{
			if (bDebug)
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Blue,
				                                 FString::Printf(TEXT("Current Angle: %f"), Current));
			FPlatformProcess::Sleep(0.001);
			Current = Gyro->yaw();
		}
	}
	getBus()->SetSpeed(0, 0);
}

void Driver::go()
{
	Lasers* Lasers = Lasers::instance();
	float Start = Lasers->readF();


	if (Start < CellDimensions::DEPTH - 5) return;
	const float Objective = Start - CellDimensions::DEPTH;
	getBus()->SetSpeed(100, 100);
	float FrontC = Lasers->readF();
	while (FrontC > Objective + 5)
	{
		float DeltaYaw = 0;
		const float Lateral = Lasers->computeLateralDifference();
		const float FrontR = Lasers->readFR(), FrontL = Lasers->readFL();

		if (Lasers::isValidWall(FrontL, FrontC, FrontR))
			DeltaYaw += Lasers::frontDifference(FrontL, FrontR) * FRONTAL_COMPENSATION_MULTIPLIER;
		else
			DeltaYaw += (FrontR > FrontL) ? -5 : 5;

		if (Lateral < LATERAL_COMPENSATION_THRESHOLD && Lateral > -LATERAL_COMPENSATION_THRESHOLD)
		{
			DeltaYaw += FMath::Clamp(Lateral * LATERAL_COMPENSATION_MULTIPLIER, -MAX_LATERAL_COMPENSATION_SPEED,
			                         MAX_LATERAL_COMPENSATION_SPEED);
		}
		getBus()->SetSpeed(100 - DeltaYaw, 100 + DeltaYaw);
		FPlatformProcess::Sleep(0.3);
		FrontC = Lasers->readF();
	}
	while (FrontC > Objective)
	{
		float DeltaYaw = 0;
		const float Lateral = Lasers->computeLateralDifference();
		const float FrontR = Lasers->readFR(), FrontL = Lasers->readFL();

		if (Lasers::isValidWall(FrontL, FrontC, FrontR))
			DeltaYaw += Lasers::frontDifference(FrontL, FrontR) * FRONTAL_COMPENSATION_MULTIPLIER;
		else
			DeltaYaw += (FrontR > FrontL) ? -5 : 5;


		if (Lateral < LATERAL_COMPENSATION_THRESHOLD / 2 && Lateral > -LATERAL_COMPENSATION_THRESHOLD / 2)
		{
			DeltaYaw += FMath::Clamp(Lateral * LATERAL_COMPENSATION_MULTIPLIER / 2, -MAX_LATERAL_COMPENSATION_SPEED / 2,
			                         MAX_LATERAL_COMPENSATION_SPEED / 2);
		}

		getBus()->SetSpeed(50 - DeltaYaw, 50 + DeltaYaw);
		FPlatformProcess::Sleep(0.1);
		FrontC = Lasers->readF();
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
