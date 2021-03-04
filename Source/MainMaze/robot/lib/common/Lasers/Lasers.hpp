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
	float ReadF() const;
	float ComputeFrontAngle() const;
	float ComputeFrontDifference() const;
	float ComputeLateralDifference() const;
	float ReadFl() const;
	float ReadFr() const;
	float ReadL() const;
	float ReadR() const;
	float ReadB() const;

	static bool IsValidWall(float l, float c, float r, int tolerance=5);
	static float FrontDifference(float l, float r);

#if _EXECUTION_ENVIRONMENT == 0
private:
	float Read(FVector direction, float delta_y = 0, bool draw=false) const;
	float MakeError(float value) const;
#endif
};
