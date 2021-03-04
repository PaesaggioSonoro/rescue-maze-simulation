// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once
#include "MainMaze/robot/lib/common/Bus/BusConnection.hpp"
#include "MainMaze/robot/utils/Singleton.hxx"
#include "MainMaze/robot/utils/Constants.hxx"

#if _EXECUTION_ENVIRONMENT == 0
#include "DrawDebugHelpers.h"
#endif

class Lasers : public Singleton<Lasers>, BusConnection
{
public:
	float readF();
	float computeFrontAngle();
	float computeFrontDifference();
	float computeLateralDifference();
	float readFL();
	float readFR();
	float readL();
	float readR();
	float readB();

	static bool isValidWall(float l, float c, float r, int tolerance=5);
	static int wallDirection(float l, float c, float r, float d, int tolerance=1);
	static float frontDifference(float l, float r);

#if _EXECUTION_ENVIRONMENT == 0
private:
	// float Read(FVector Vector, FVector Direction);
	float Read(FVector Direction, float DeltaY = 0, bool Draw=false);
	float MakeError(float value);
#endif
};
