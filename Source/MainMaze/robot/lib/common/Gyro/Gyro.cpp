#include "Gyro.hpp"

#if _EXECUTION_ENVIRONMENT == 0
void Gyro::Start(unsigned long refresh)
{
	const auto now = high_resolution_clock::now();
	last_reset_time_ = duration_cast<milliseconds>(now.time_since_epoch()).count();
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
	const auto now = high_resolution_clock::now();
	last_reset_time_ = duration_cast<milliseconds>(now.time_since_epoch()).count();
}

float Gyro::CalculateError()
{
	if (error_)
	{
		const auto now = high_resolution_clock::now();
		const auto millis = duration_cast<milliseconds>(now.time_since_epoch()).count();
		const auto current_error = drift_ * (millis - last_reset_time_) / 1000 - FMath::RandRange(0, 1);
		return current_error;
	}
	return 0.0;
}
#endif
