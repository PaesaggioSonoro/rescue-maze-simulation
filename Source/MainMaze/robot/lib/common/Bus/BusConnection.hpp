#pragma once

#if _EXECUTION_ENVIRONMENT == 0
#include "MainMaze/DrivableActor.h"
#endif


class BusConnection
{
#if _EXECUTION_ENVIRONMENT == 0
	static DrivableActor* bus_;
public:
	static void SetBus(DrivableActor* actor);
	static DrivableActor* GetBus();
#endif
};
