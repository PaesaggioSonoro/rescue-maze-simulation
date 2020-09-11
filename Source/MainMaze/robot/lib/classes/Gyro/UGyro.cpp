#include "UGyro.hpp"


UGyro::UGyro(DrivableActor* actor)
{
    this->actor = actor;
}

void UGyro::start(unsigned long refresh)
{
}

float UGyro::yaw()
{
    return actor->GetActor()->GetActorRotation().Yaw + CalculateError();
}

float UGyro::roll()
{
    return actor->GetActor()->GetActorRotation().Roll + CalculateError();
}

float UGyro::pitch()
{
    return actor->GetActor()->GetActorRotation().Pitch + CalculateError();
}

void UGyro::calibrate()
{
    max_error = 0.0;
}

float UGyro::CalculateError()
{
    if (error)
    {
        srand(static_cast<int>(time(nullptr)));
        auto now = high_resolution_clock::now();
        auto nanos = duration_cast<nanoseconds>(now.time_since_epoch()).count();
        srand(nanos);
        max_error += ((rand() % 100) - 50) / (500.0 * (1 / drift));

        return max_error;
    }
    return 0.0;
}
