#pragma once
#include "../utils/singleton.hpp"
#include "ServiceLocator.hpp"

class RobotServiceLocator : public Singleton<RobotServiceLocator>
{
public:
    RobotServiceLocator();
// #if _EXECUTION_ENVIRONMENT=0
//
// #else
//     
// #endif

private:
    sptr<ServiceLocator> sl;
};
