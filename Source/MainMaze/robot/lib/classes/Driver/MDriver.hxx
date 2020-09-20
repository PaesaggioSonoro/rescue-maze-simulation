#pragma once
#include "UDriver.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "MainMaze/robot/lib/interfaces/IDriver.hh"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

class MDriver : public ServiceLocator::Module
{
public:
    virtual ~MDriver() = default;

    void load() override
    {
        bind<IDriver>().to<UDriver>([](SLContext_sptr slc)
        {
            return new UDriver(slc->resolve<IBus>()->getBus());
        }).asSingleton();
    }
};
