#pragma once

#include "MainMaze/robot/lib/interfaces/ISerial.hh"

#include "Core/Public/Windows/AllowWindowsPlatformTypes.h"
#include "Windows.h"
#include "Core/Public/Windows/HideWindowsPlatformTypes.h"

class USerial : public ISerial
{
public:
    USerial(const char* portName, int baud_rate);
    int read(char* buffer, unsigned size) override;
    bool write(char buffer[], unsigned size) override;
    void close() override;
    ~USerial();

private:
    HANDLE Handler;
    bool bConnected{};
    COMSTAT Status{};
    DWORD Errors{};
};
