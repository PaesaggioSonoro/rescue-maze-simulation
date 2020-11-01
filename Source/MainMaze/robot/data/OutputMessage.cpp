// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#include "OutputMessage.hpp"
#include "MainMaze/robot/utils/Constants.hxx"

OutputMessage::OutputMessage(Walls walls, bool black, bool checkpoint, bool ramp, bool obstacle)
    : walls(&walls),
      black(black),
      checkpoint(checkpoint),
      ramp(ramp),
      obstacle(obstacle)
{
}

OutputMessage::OutputMessage(char* data)
{
    Walls in_walls = std::make_tuple(data[0], data[1], data[2], data[3]);
    this->walls = &in_walls;
    const int o = Communication::FLAGS_OFFSET;
    black = checkpoint = ramp = obstacle = false;
    for (int i = o; i < Communication::MESSAGE_LENGTH; ++i)
    {
        if (data[i] == 'B') black = true;
        if (data[i] == 'C') checkpoint = true;
        if (data[i] == 'R') ramp = true;
        if (data[i] == 'O') obstacle = true;
    }
}

char* OutputMessage::toBinary() const
{
    static char out[Communication::MESSAGE_LENGTH] = {};
    const int o = Communication::FLAGS_OFFSET;
    copyTuple4(out, *walls);
    if (black) out[o + 0] = 'B';
    if (checkpoint) out[o + 1] = 'C';
    if (ramp) out[o + 2] = 'R';
    if (obstacle) out[o + 3] = 'O';
    return out;
}
