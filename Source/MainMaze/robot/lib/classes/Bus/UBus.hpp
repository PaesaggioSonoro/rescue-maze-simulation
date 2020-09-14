#pragma once
#include "MainMaze/DrivableActor.h"
#include "MainMaze/robot/lib/interfaces/IBus.hh"

class UBus : public IBus
{
public:
    UBus();
    DrivableActor* Bus = nullptr;
    void setBus(DrivableActor* Actor) override;
    DrivableActor* getBus() override;
};
