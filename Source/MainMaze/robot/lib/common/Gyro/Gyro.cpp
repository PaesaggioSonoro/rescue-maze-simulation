#include "Gyro.hpp"

#if _EXECUTION_ENVIRONMENT == 0
void Gyro::Start(unsigned long refresh)
{
}

float Gyro::Yaw()
{
	return FRotator::ClampAxis(GetBus()->GetActor()->GetActorRotation().Yaw + CalculateError());
}

float Gyro::Roll()
{
	return FRotator::ClampAxis(GetBus()->GetActor()->GetActorRotation().Roll + CalculateError());
}

float Gyro::Pitch()
{
	return FRotator::ClampAxis(GetBus()->GetActor()->GetActorRotation().Pitch + CalculateError());
}

void Gyro::Calibrate()
{
	max_error_ = 0.0;
}

float Gyro::CalculateError()
{
	if (error_)
	{
		srand(static_cast<int>(time(nullptr)));
		const auto now = high_resolution_clock::now();
		const auto nanos = duration_cast<nanoseconds>(now.time_since_epoch()).count();
		srand(nanos);
		max_error_ += ((rand() % 100) - 50) / (500.0 * (1 / drift_));

		return max_error_;
	}
	return 0.0;
}
#endif
