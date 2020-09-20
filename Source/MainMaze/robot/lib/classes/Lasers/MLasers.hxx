#pragma once
#include "ULasers.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "MainMaze/robot/lib/interfaces/ILasers.hh"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

class MLasers : public ServiceLocator::Module
{
public:
    virtual ~MLasers() = default;

    void load() override
    {
        bind<ILasers>().to<ULasers>([](SLContext_sptr slc)
        {
            return new ULasers(slc->resolve<IBus>()->getBus());
        }).asSingleton();
    }
};
