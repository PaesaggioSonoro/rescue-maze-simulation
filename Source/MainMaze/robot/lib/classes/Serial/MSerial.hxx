#pragma once
#include "USerial.hpp"
#include "MainMaze/robot/lib/interfaces/ISerial.hh"
#include "MainMaze/robot/servicelocator/ServiceLocator.hxx"

class MSerial : public ServiceLocator::Module
{
public:
    void load() override
    {
        bind<ISerial>().to<USerial>([](SLContext_sptr /*slc*/)
        {
            return new USerial("COM3", 9600);
        }).asSingleton();
    }
};
