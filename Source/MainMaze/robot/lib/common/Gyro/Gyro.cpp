// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#include "Gyro.hpp"

#if _EXECUTION_ENVIRONMENT == 0
void Gyro::start(unsigned long refresh)
{
}

float Gyro::yaw()
{
	return FRotator::ClampAxis(getBus()->GetActor()->GetActorRotation().Yaw + CalculateError());
}

float Gyro::roll()
{
	return FRotator::ClampAxis(getBus()->GetActor()->GetActorRotation().Roll + CalculateError());
}

float Gyro::pitch()
{
	return FRotator::ClampAxis(getBus()->GetActor()->GetActorRotation().Pitch + CalculateError());
}

void Gyro::calibrate()
{
	Max_Error = 0.0;
}

float Gyro::CalculateError()
{
	if (bError)
	{
		srand(static_cast<int>(time(nullptr)));
		const auto now = high_resolution_clock::now();
		const auto nanos = duration_cast<nanoseconds>(now.time_since_epoch()).count();
		srand(nanos);
		Max_Error += ((rand() % 100) - 50) / (500.0 * (1 / Drift));

		return Max_Error;
	}
	return 0.0;
}
#endif
