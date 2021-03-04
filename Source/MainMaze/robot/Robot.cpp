#include "Robot.hpp"


#include "lib/common/Driver/Driver.hpp"
#include "lib/common/Lasers/Lasers.hpp"
#include "lib/common/Serial/Serial.hpp"
#include "lib/common/Temp/Temp.hpp"

void Robot::Setup()
{
	Lasers* lasers = Lasers::Instance();
	Temp* temps = Temp::Instance();
	Driver* driver = Driver::Instance();
	Serial* serial = Serial::Instance();

	// for (int i = 0; i < 10000; ++i)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Emerald,FString::Printf(TEXT("Angle: %f"), FMath::RadiansToDegrees(lasers->computeFrontAngle())));
	// 	FPlatformProcess::Sleep(0.2);
	// }

	// Walls walls = std::make_tuple(0x00, 0x01, 0x00, 0x01);
	// Walls walls{0x00, 0x01, 0x01, 0x01};
	// OutputMessage message(walls, true, false, true, false);
	//
	// FPlatformProcess::Sleep(0.1);
	//
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
	//                                  FString::Printf(
	//                                      TEXT("Serial: %d"),
	//                                      serial->write(message.toBinary(), Communication::MESSAGE_LENGTH)));
	// serial->close();
	driver->Rotate(true);
	driver->Go();
	driver->Go();
	driver->Go();
	driver->Rotate(false);
	driver->Go();
	driver->Rotate(true);
	driver->Go();
	driver->Rotate(true);
	driver->Go();
	driver->Go();
	driver->Rotate(false);
	driver->Go();
	driver->Go();
	driver->Rotate(true);
	driver->Go();
	driver->Go();
	driver->Rotate(true);
	driver->Go();
	driver->Go();
	driver->Go();
	driver->Rotate(true);
	driver->Go();
	driver->Rotate(false);
	driver->Go();
	driver->Go();
	// driver->rotate(false);
	// driver->rotate(false);
	// driver->go();
	// driver->rotate(true);
	// driver->go();
	// driver->go();
	// driver->go();
	
	
	// driver->rotate(false);
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

void Robot::Main()
{
}
