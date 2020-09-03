#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Math/Vector.h"


struct Point
{
	float x, y;
	Point() {}
	Point(float x_, float y_)
	{
		x = x_;
		y = y_;
	}
	void rotate(Point pivot, float angle)
	{
		angle *= M_PI / 180;
		float s = sin(angle);
		float c = cos(angle);

		float x_ = c * (x - pivot.x) - s * (y - pivot.y) + pivot.x;
		float y_ = s * (x - pivot.x) + c * (y - pivot.y) + pivot.y;
		x = x_;
		y = y_;
	}
	FVector toVector(float z)
	{
		return FVector(x, y, z);
	}
};
