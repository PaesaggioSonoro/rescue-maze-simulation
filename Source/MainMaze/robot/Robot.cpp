#include "Robot.h"


#include "servicelocator/RobotServiceLocator.h"
#include "MainMaze/robot/lib/interfaces/IBus.h"
#include "MainMaze/robot/lib/interfaces/IGyro.h"

void Robot::setup()
{
    auto& rsl = RobotServiceLocator::instance();
    UE_LOG(LogTemp, Warning, TEXT("YAW: %f"), rsl.sl()->getContext()->resolve<IGyro>()->yaw());
}

void Robot::main()
{
}
