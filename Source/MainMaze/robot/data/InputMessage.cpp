// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#include "InputMessage.hpp"
#include "MainMaze/robot/utils/Constants.hxx"

InputMessage::InputMessage(Direction direction, bool drop, bool climb, bool old)
    : direction(&direction),
      drop(drop),
      climb(climb),
      old(old)
{
}

InputMessage::InputMessage(char* data)
{
    Direction in_direction = std::make_tuple(data[0], data[1], data[2], data[3]);
    this->direction = &in_direction;
    const int o = Communication::FLAGS_OFFSET;
    drop = climb = old = false;
    for (int i = o; i < Communication::MESSAGE_LENGTH; ++i)
    {
        if (data[i] == 'D') drop = true;
        if (data[i] == 'C') climb = true;
        if (data[i] == 'O') old = true;
    }
}

char* InputMessage::toBinary() const
{
    static char out[Communication::MESSAGE_LENGTH] = {};
    const int o = Communication::FLAGS_OFFSET;
    copyTuple4(out, *direction);
    if (drop) out[o + 0] = 'D';
    if (climb) out[o + 1] = 'C';
    if (old) out[o + 2] = 'O';
    return out;
}
