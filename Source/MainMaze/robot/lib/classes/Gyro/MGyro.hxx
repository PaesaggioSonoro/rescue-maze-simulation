#pragma once
#include "UGyro.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "MainMaze/robot/lib/interfaces/IGyro.hh"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

class MGyro : public ServiceLocator::Module
{
public:
    virtual ~MGyro() = default;

    void load() override
    {
        bind<IGyro>().to<UGyro>([](SLContext_sptr slc)
        {
            return new UGyro(slc->resolve<IBus>()->getBus());
        }).asSingleton();
    }
};
