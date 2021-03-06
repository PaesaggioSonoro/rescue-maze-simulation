#pragma once
#include "MainMaze/robot/data/Directions.hxx"
#include "MainMaze/robot/utils/Singleton.hxx"
#include "MainMaze/robot/lib/common/Driver/Driver.hpp"

class Compass : public Singleton<Compass>
{
	direction direction_ = kTop;

public:
	void GoTo(const direction objective);
};
