#include "RobotServiceLocator.h"

#include "MainMaze/robot/lib/classes/Bus/MBus.hpp"
#include "MainMaze/robot/lib/classes/Gyro/MGyro.hpp"


RobotServiceLocator::RobotServiceLocator()
{
    _sl = ServiceLocator::create();
    _sl->modules()
    .add<MBus>()
    .add<MGyro>();
}

sptr<ServiceLocator> RobotServiceLocator::sl()
{
    return _sl;
}
