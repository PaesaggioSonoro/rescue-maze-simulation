#pragma once

#if _EXECUTION_ENVIRONMENT == 0
#include "DrawDebugHelpers.h"
#include "MainMaze/Wall.h"
#endif

#include "MainMaze/robot/lib/common/Bus/BusConnection.hpp"
#include "MainMaze/robot/utils/GeometricPair.hxx"
#include "MainMaze/robot/utils/Singleton.hxx"

class Temp : public Singleton<Temp>, BusConnection
{
public:
	float threshold = 0;
	void Calibrate();
	GeometricPair<float> Read() const;
	GeometricPair<bool> IsHot() const;

#if _EXECUTION_ENVIRONMENT == 0
private:
	float ReadSide(FVector direction) const;
#endif
};
