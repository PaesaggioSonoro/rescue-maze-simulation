#pragma once

#include "MainMaze/robot/lib/common/Gyro/Gyro.hpp"
#include "MainMaze/robot/lib/common/Lasers/Lasers.hpp"
#include "MainMaze/robot/lib/common/Bus/BusConnection.hpp"
#include "MainMaze/robot/utils/Singleton.hxx"

class Driver : public Singleton<Driver>, BusConnection
{
	const float MAX_LATERAL_COMPENSATION_SPEED = 5;
	const float LATERAL_COMPENSATION_THRESHOLD = 10;
	const float LATERAL_COMPENSATION_MULTIPLIER = 6;
	const float FRONTAL_COMPENSATION_MULTIPLIER = 10;
public:
	void rotate(bool right);
	void go();

#if _EXECUTION_ENVIRONMENT == 0
private:
	static bool RightTurnCondition(float Start, float Current, float Goal);
	static bool LeftTurnCondition(float Start, float Current, float Goal);
#endif
};
