#pragma once
#include "../utils/Singleton.hpp"
#include "ServiceLocator.hpp"


class RobotServiceLocator : public Singleton<RobotServiceLocator>
{
public:
    RobotServiceLocator();

    sptr<ServiceLocator> sl();

private:
    sptr<ServiceLocator> _sl;
};
