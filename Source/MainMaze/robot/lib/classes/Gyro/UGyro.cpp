// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#include "UGyro.hpp"


UGyro::UGyro(DrivableActor* Actor)
{
    this->Actor = Actor;
}

void UGyro::start(unsigned long refresh)
{
}

float UGyro::yaw()
{
    return Actor->GetActor()->GetActorRotation().Yaw + CalculateError();
}

float UGyro::roll()
{
    return Actor->GetActor()->GetActorRotation().Roll + CalculateError();
}

float UGyro::pitch()
{
    return Actor->GetActor()->GetActorRotation().Pitch + CalculateError();
}

void UGyro::calibrate()
{
    Max_Error = 0.0;
}

float UGyro::CalculateError()
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
