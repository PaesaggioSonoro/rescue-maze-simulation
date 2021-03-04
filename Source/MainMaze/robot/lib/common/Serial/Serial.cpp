#include "Serial.hpp"


#if _EXECUTION_ENVIRONMENT == 0


void Serial::Connect(const char* port_name, const int baud_rate)
{
	this->handler_ = CreateFileA(port_name,
	                            GENERIC_READ | GENERIC_WRITE,
	                            0,
	                            nullptr,
	                            OPEN_EXISTING,
	                            FILE_ATTRIBUTE_NORMAL,
	                            nullptr);
	if (this->handler_ == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error opening serial port " << port_name << "\n";
		return;
	}

	DCB dcb_serial_params = {0};
	dcb_serial_params.DCBlength = sizeof(dcb_serial_params);

	GetCommState(this->handler_, &dcb_serial_params);

	dcb_serial_params.BaudRate = baud_rate; // Setting BaudRate = 9600
	dcb_serial_params.ByteSize = 8; // Setting ByteSize = 8
	dcb_serial_params.StopBits = ONESTOPBIT; // Setting StopBits = 1
	dcb_serial_params.Parity = NOPARITY; // Setting Parity = None
	dcb_serial_params.fDtrControl = DTR_CONTROL_ENABLE;

	PurgeComm(this->handler_, PURGE_RXCLEAR | PURGE_TXCLEAR);

	SetCommState(this->handler_, &dcb_serial_params);
}

int Serial::Read(char* buffer, const unsigned size) const
{
	DWORD bytes_read{};
	const unsigned int bytes_to_read = size;
	memset(buffer, 0, size);
	ReadFile(this->handler_, buffer, bytes_to_read, &bytes_read, nullptr);
	return bytes_read;
}

bool Serial::Write(char buffer[], const unsigned size) const
{
	DWORD bytes_written; // No of bytes written to the port

	return WriteFile(this->handler_, // Handle to the Serial port
	                 buffer, // Data to be written to the port
	                 size, //No of bytes to write
	                 &bytes_written, //Bytes written
	                 nullptr);
}

void Serial::Close() const
{
	CloseHandle(this->handler_); //Closing the Serial Port
}

Serial::~Serial()
{
	CloseHandle(this->handler_); //Closing the Serial Port
}
#endif
