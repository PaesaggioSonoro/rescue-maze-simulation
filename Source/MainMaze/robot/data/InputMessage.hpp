// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once
#include "Directions.hxx"
#include "IMessage.hh"

class InputMessage final : public IMessage
{
    Direction* direction;
    bool drop;
    bool climb;
    bool old;
public:
    InputMessage(Direction direction, bool drop, bool climb, bool old);

    explicit InputMessage(char* data);

    char* toBinary() const override;
};
