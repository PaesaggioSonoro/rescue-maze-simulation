#pragma once

#include "MainMaze/robot/lib/common/Gyro/Gyro.hpp"
#include "MainMaze/robot/lib/common/Lasers/Lasers.hpp"
#include "MainMaze/robot/lib/common/Bus/BusConnection.hpp"
#include "MainMaze/robot/utils/Singleton.hxx"

class Driver : public Singleton<Driver>, BusConnection
{
	const float max_lateral_compensation_speed_ = 5;
	const float lateral_compensation_threshold_ = 10;
	const float lateral_compensation_multiplier_ = 10;
	const float frontal_compensation_multiplier_ = 5;
	const int stuck_compensation_multiplier_ = 35;
	const int degree_override_threshold_ = 5;

	enum Speeds { kSlow=30, kMedium=50, kFast=100 };

	const bool debug_ = false;

public:
	void Rotate(bool right);
	void Go();

#if _EXECUTION_ENVIRONMENT == 0
private:
	static bool RightTurnCondition(float start, float current, float goal);
	static bool LeftTurnCondition(float start, float current, float goal);
#endif
};
