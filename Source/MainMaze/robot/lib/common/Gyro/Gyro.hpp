#pragma once
#include <chrono>
#include <ctime>


#include "MainMaze/robot/lib/common/Bus/BusConnection.hpp"
#include "MainMaze/robot/utils/Singleton.hxx"

using namespace std::chrono;

class Gyro : public Singleton<Gyro>, BusConnection
{
public:
	void start(unsigned long refresh);
	float yaw();
	float roll();
	float pitch();
	void calibrate();

#if _EXECUTION_ENVIRONMENT == 0
private:
	float Drift = 1;
	bool bError = true;
	float CalculateError();
	float Max_Error = 0.0;
#endif
};
