#pragma once

class DrivableActor
{
protected:
    ~DrivableActor() = default;
public:

    virtual FRotator GetRotator() = 0;

    // Actuation
    virtual void SetSpeedR(int speed) = 0;
    virtual void SetSpeedL(int speed) = 0;
    virtual void SetSpeed(int speedL, int speedR) = 0;
};
