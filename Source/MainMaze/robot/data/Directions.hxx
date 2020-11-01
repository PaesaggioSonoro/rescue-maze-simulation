// ReSharper disable CppUE4CodingStandardNamingViolationWarning
#pragma once
#include <tuple>

typedef const std::tuple<char, char, char, char> Direction;
typedef const std::tuple<char, char, char, char> Walls;

namespace VDirection
{
    Direction const RIGHT = std::make_tuple(0x01, 0, 0, 0);
    Direction const TOP = std::make_tuple(0, 0x01, 0, 0);
    Direction const LEFT = std::make_tuple(0, 0, 0x01, 0);
    Direction const BOTTOM = std::make_tuple(0, 0, 0, 0x01);
};

inline void copyTuple4(char* arr, Direction direction, int offset = 0)
{
    arr[offset + 0] = std::get<0>(direction);
    arr[offset + 1] = std::get<1>(direction);
    arr[offset + 2] = std::get<2>(direction);
    arr[offset + 3] = std::get<3>(direction);
}
