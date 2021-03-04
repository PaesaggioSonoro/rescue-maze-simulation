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
	void Connect(const char* port_name, int baud_rate);
	int Read(char* buffer, unsigned size) const;
	bool Write(char buffer[], unsigned size) const;
	void Close() const;
	~Serial();

#if _EXECUTION_ENVIRONMENT == 0
private:
	HANDLE handler_ = nullptr;
	bool connected_{};
	COMSTAT status_{};
	DWORD errors_{};
#endif
};
