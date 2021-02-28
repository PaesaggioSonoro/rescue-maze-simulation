#include "Driver.hpp"


#if _EXECUTION_ENVIRONMENT == 0

void Driver::rotate(bool right)
{
	bool bDebug = false;
	Gyro* Gyro = Gyro::instance();
	float Start = Gyro->yaw();
	if (right)
	{
		float Goal = FRotator::ClampAxis(Start + 80);
		getBus()->SetSpeed(50, -50);
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
		float Goal = FRotator::ClampAxis(Start - 80);
		getBus()->SetSpeed(-50, 50);
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


	if (Start < 30.0) return;
	getBus()->SetSpeed(100, 100);
	while (Lasers->readF() > Start - 30)
	{
		float DeltaYaw = Lasers->computeFrontDifference() * 10;
		GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red,
		                                 FString::Printf(TEXT("FrontAngle: %f"), DeltaYaw));
		getBus()->SetSpeed(80 - DeltaYaw, 80 + DeltaYaw);
		FPlatformProcess::Sleep(0.2);
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
