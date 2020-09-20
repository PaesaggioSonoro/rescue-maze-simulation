#include "RobotServiceLocator.hpp"

#include "MainMaze/robot/lib/classes/Bus/MBus.hxx"
#include "MainMaze/robot/lib/classes/Driver/MDriver.hxx"
#include "MainMaze/robot/lib/classes/Gyro/MGyro.hxx"
#include "MainMaze/robot/lib/classes/Lasers/MLasers.hxx"
#include "MainMaze/robot/lib/classes/Temp/MTemp.hxx"


RobotServiceLocator::RobotServiceLocator()
{
    _sl = ServiceLocator::create();
    _sl->modules()
       .add<MBus>()
       .add<MGyro>()
       .add<MTemp>()
       .add<MLasers>()
       .add<MDriver>();
}

sptr<ServiceLocator> RobotServiceLocator::sl()
{
    return _sl;
}
