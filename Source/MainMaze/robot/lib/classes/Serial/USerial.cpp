#include "USerial.hpp"


USerial::USerial(const char* portName, int baud_rate)
{
    this->Handler = CreateFileA(static_cast<LPCSTR>(portName),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                nullptr,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                nullptr);
    if (this->Handler == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error opening serial port " << portName << "\n";
        return;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    GetCommState(this->Handler, &dcbSerialParams);

    dcbSerialParams.BaudRate = baud_rate; // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8; // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT; // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY; // Setting Parity = None
    dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

    PurgeComm(this->Handler, PURGE_RXCLEAR | PURGE_TXCLEAR);

    SetCommState(this->Handler, &dcbSerialParams);
}

int USerial::read(char* buffer, unsigned size)
{
    DWORD bytesRead{};
    const unsigned int toRead = size;
    memset(static_cast<void*>(buffer), 0, size);
    ReadFile(this->Handler, static_cast<void*>(buffer), toRead, &bytesRead, nullptr);
    return bytesRead;
}

bool USerial::write(char buffer[], unsigned size)
{
    DWORD BytesWritten; // No of bytes written to the port

    return WriteFile(this->Handler, // Handle to the Serial port
                     static_cast<void*>(buffer), // Data to be written to the port
                     size, //No of bytes to write
                     &BytesWritten, //Bytes written
                     nullptr);
}

void USerial::close()
{
    CloseHandle(this->Handler); //Closing the Serial Port
}

USerial::~USerial()
{
    CloseHandle(this->Handler); //Closing the Serial Port
}
