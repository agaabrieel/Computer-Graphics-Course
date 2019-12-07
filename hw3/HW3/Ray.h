#pragma once
#include "Point.h"
#include "Direction.h"

/*
A ray has:

An Origin (Point)
A Direction

*/


class Ray
{
	public:
		Ray(Point origin, Direction direction);

	private:
		const Point origin;
		const Direction direction;
};

