#pragma once
#include "../utils/Singleton.hxx"
#include "ServiceLocator.hxx"


class RobotServiceLocator : public Singleton<RobotServiceLocator>
{
public:
    RobotServiceLocator();

    sptr<ServiceLocator> sl();

private:
    sptr<ServiceLocator> _sl;
};
