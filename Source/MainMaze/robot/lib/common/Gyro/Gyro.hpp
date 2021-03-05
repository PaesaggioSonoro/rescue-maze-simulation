#pragma once
#include <chrono>
#include <ctime>


#include "MainMaze/robot/lib/common/Bus/BusConnection.hpp"
#include "MainMaze/robot/utils/Singleton.hxx"

using namespace std::chrono;

class Gyro : public Singleton<Gyro>, BusConnection
{
public:
	void Start(unsigned long refresh);
	float Yaw();
	float Roll();
	float Pitch();
	void Calibrate();

#if _EXECUTION_ENVIRONMENT == 0
private:
	float drift_ = 0.2;
	bool error_ = true;
	float CalculateError();
	long long last_reset_time_ = 0;
#endif
};
