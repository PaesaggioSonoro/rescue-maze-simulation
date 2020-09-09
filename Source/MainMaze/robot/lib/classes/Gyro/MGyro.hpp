#pragma once
#include "UGyro.h"
#include "MainMaze/robot/lib/interfaces/IBus.h"
#include "MainMaze/robot/lib/interfaces/IGyro.h"
#include "MainMaze/robot/servicelocator/ServiceLocator.hpp"

class MGyro : public ServiceLocator::Module
{
public:
    void load() override
    {
        bind<IGyro>().to<UGyro>([] (SLContext_sptr slc)
        {
            return new UGyro(slc->resolve<IBus>()->GetBus());
        }).asSingleton();
    }
};
