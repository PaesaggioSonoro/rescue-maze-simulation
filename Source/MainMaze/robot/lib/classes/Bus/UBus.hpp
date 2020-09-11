#pragma once
#include "MainMaze/DrivableActor.h"
#include "MainMaze/robot/lib/interfaces/IBus.hh"

class UBus : public IBus
{
public:
    UBus();
    DrivableActor* Bus = nullptr;
    void SetBus(DrivableActor* Actor) override;
    DrivableActor* GetBus() override;
};
