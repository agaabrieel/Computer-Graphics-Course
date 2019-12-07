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
		~Ray();

		Point origin() const;
		Direction direction() const;

	private:
		const Point _origin;
		const Direction _direction;
};

