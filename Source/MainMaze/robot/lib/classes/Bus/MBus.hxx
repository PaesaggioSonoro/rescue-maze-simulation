#pragma once
#include "UBus.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

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
