#pragma once
#include "UBus.h"
#include "MainMaze/robot/lib/interfaces/IBus.h"
#include "MainMaze/robot/servicelocator/ServiceLocator.hpp"

class MBus : public ServiceLocator::Module
{
public:
    void load() override
    {
        bind<IBus>().to<UBus>([](SLContext_sptr slc)
        {
            return new UBus();
        }).asSingleton();
    }
};
