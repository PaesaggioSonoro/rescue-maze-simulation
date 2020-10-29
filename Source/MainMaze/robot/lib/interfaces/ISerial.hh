#pragma once

class ISerial
{
public:
    virtual bool write(char buffer[], unsigned int size) = 0;
    virtual int read(char* buffer, unsigned int size) = 0;
    virtual void close() = 0;
    virtual ~ISerial() = default;
};
