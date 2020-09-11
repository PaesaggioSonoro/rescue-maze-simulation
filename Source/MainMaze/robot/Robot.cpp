#include "Robot.hpp"


#include "lib/interfaces/ITemp.hh"
#include "servicelocator/RobotServiceLocator.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "MainMaze/robot/lib/interfaces/IGyro.hh"

void Robot::setup()
{
    auto& rsl = RobotServiceLocator::instance();
    UE_LOG(LogTemp, Warning, TEXT("YAW: %f"), rsl.sl()->getContext()->resolve<IGyro>()->yaw());

    sptr<ITemp> temp = rsl.sl()->getContext()->resolve<ITemp>();
    temp->calibrate();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance R: %f"), temp->read().right));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance L: %f"), temp->read().left));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance R: %d"), temp->isHot().right));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance L: %d"), temp->isHot().left));
    }
}

void Robot::main()
{
}
