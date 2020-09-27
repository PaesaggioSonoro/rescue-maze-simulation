#include "Robot.hpp"


#include "lib/interfaces/IDriver.hh"
#include "lib/interfaces/ILasers.hh"
#include "lib/interfaces/ITemp.hh"
#include "servicelocator/RobotServiceLocator.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"

void Robot::setup()
{
    auto& rsl = RobotServiceLocator::instance();

    sptr<ILasers> lasers = rsl.sl()->getContext()->resolve<ILasers>();
    sptr<ITemp> temps = rsl.sl()->getContext()->resolve<ITemp>();
    sptr<IDriver> driver = rsl.sl()->getContext()->resolve<IDriver>();
    
    driver->rotate(true);
    driver->go();
    driver->go();
    driver->go();
    driver->rotate(false);
    driver->go();
    driver->rotate(true);
    driver->go();
    driver->rotate(true);
    driver->go();
    driver->go();
    driver->rotate(false);
    driver->go();
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance F: %f"), lasers->readF()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance FR: %f"), lasers->readFR()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance FL: %f"), lasers->readFL()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance R: %f"), lasers->readR()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance L: %f"), lasers->readL()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
                                         FString::Printf(TEXT("Distance B: %f"), lasers->readB()));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
                                        FString::Printf(TEXT("Temp R: %f"), temps->read().right));
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
                                        FString::Printf(TEXT("Temp L: %f"), temps->read().left));
    }
    
    // if (GEngine)
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                      FString::Printf(TEXT("Distance F: %f"), lasers->readF()));
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                      FString::Printf(TEXT("Distance FR: %f"), lasers->readFR()));
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                      FString::Printf(TEXT("Distance FL: %f"), lasers->readFL()));
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                      FString::Printf(TEXT("Distance R: %f"), lasers->readR()));
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                      FString::Printf(TEXT("Distance L: %f"), lasers->readL()));
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                      FString::Printf(TEXT("Distance B: %f"), lasers->readB()));
    // }
    // driver->go();
    // driver->rotate(true);
    // driver->go();
    // driver->go();
    // driver->rotate(false);
    // driver->go();
    // driver->rotate(true);
    // driver->go();
}

void Robot::main()
{
}
