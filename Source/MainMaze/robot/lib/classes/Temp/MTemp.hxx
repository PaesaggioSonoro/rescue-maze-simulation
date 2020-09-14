#pragma once
#include "UTemp.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "MainMaze/robot/lib/interfaces/ITemp.hh"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

class MTemp : public ServiceLocator::Module
{
public:
    void load() override
    {
        bind<ITemp>().to<UTemp>([](SLContext_sptr slc)
        {
            return new UTemp(slc->resolve<IBus>()->getBus());
        });
    }
};
