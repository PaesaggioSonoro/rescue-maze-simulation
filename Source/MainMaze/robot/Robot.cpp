#include "Robot.hpp"


#include "data/InputMessage.hpp"
#include "data/OutputMessage.hpp"
#include "lib/interfaces/IDriver.hh"
#include "lib/interfaces/ILasers.hh"
#include "lib/interfaces/ISerial.hh"
#include "lib/interfaces/ITemp.hh"
#include "servicelocator/RobotServiceLocator.hpp"
#include "MainMaze/robot/lib/interfaces/IBus.hh"
#include "utils/Constants.hxx"

void Robot::setup()
{
    auto& rsl = RobotServiceLocator::instance();

    sptr<ILasers> lasers = rsl.sl()->getContext()->resolve<ILasers>();
    sptr<ITemp> temps = rsl.sl()->getContext()->resolve<ITemp>();
    sptr<IDriver> driver = rsl.sl()->getContext()->resolve<IDriver>();
    sptr<ISerial> serial = rsl.sl()->getContext()->resolve<ISerial>();

    // Walls walls = std::make_tuple(0x00, 0x01, 0x00, 0x01);
    // Walls walls{0x00, 0x01, 0x01, 0x01};
    // OutputMessage message(walls, true, false, true, false);
    //
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                  FString::Printf(
    //                                      TEXT("Serial: %d"),
    //                                      serial->write(message.toBinary(), Communication::MESSAGE_LENGTH)));
    // FPlatformProcess::Sleep(0.1);
    //
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
    //                                  FString::Printf(
    //                                      TEXT("Serial: %d"),
    //                                      serial->write(message.toBinary(), Communication::MESSAGE_LENGTH)));
    serial->close();
    driver->rotate(true);
    driver->go();
    driver->go();
    driver->go();
    driver->rotate(false);
    // driver->go();
    // driver->rotate(true);
    // driver->go();
    // driver->rotate(true);
    // driver->go();
    // driver->go();
    // driver->rotate(false);
    // driver->go();
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
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
    //                                     FString::Printf(TEXT("Temp R: %f"), temps->read().right));
    //     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
    //                                     FString::Printf(TEXT("Temp L: %f"), temps->read().left));
    // }

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
