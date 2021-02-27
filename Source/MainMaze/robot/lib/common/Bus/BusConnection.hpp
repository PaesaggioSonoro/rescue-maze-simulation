// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

#if _EXECUTION_ENVIRONMENT == 0
#include "MainMaze/DrivableActor.h"
#endif


class BusConnection
{
#if _EXECUTION_ENVIRONMENT == 0
	static DrivableActor* _Bus;
public:
	static void setBus(DrivableActor* Actor);
	static DrivableActor* getBus();
#endif
};
