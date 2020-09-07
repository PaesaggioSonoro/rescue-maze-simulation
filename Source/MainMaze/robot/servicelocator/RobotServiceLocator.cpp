#include "RobotServiceLocator.h"


RobotServiceLocator::RobotServiceLocator()
{
    sl = ServiceLocator::create();
    GLog->Log("Constructed");
}
