// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once

#include "MainMaze/robot/lib/common/Bus/BusConnection.hpp"
#include "MainMaze/robot/utils/Singleton.hxx"

#if _EXECUTION_ENVIRONMENT == 0
#include "Core/Public/Windows/AllowWindowsPlatformTypes.h"
#include "Windows.h"
#include <iostream>
#include "Core/Public/Windows/HideWindowsPlatformTypes.h"
#endif


class Serial : public Singleton<Serial>, BusConnection
{
public:
	void connect(const char* portName, int baud_rate);
	int read(char* buffer, unsigned size);
	bool write(char buffer[], unsigned size);
	void close();
	~Serial();

#if _EXECUTION_ENVIRONMENT == 0
private:
	HANDLE Handler = nullptr;
	bool bConnected{};
	COMSTAT Status{};
	DWORD Errors{};
#endif
};
