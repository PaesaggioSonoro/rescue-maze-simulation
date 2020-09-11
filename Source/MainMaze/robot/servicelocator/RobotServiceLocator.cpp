#include "RobotServiceLocator.hpp"

#include "MainMaze/robot/lib/classes/Bus/MBus.hxx"
#include "MainMaze/robot/lib/classes/Gyro/MGyro.hxx"
#include "MainMaze/robot/lib/classes/Temp/MTemp.hxx"


RobotServiceLocator::RobotServiceLocator()
{
    _sl = ServiceLocator::create();
    _sl->modules()
       .add<MBus>()
       .add<MGyro>()
       .add<MTemp>();
}

sptr<ServiceLocator> RobotServiceLocator::sl()
{
    return _sl;
}
