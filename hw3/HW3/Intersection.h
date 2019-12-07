#pragma once
#include "Shape.h"
#include "Point.h"

/*
An Intersection has:

The shape that was hit
The Point where the ray hit


*/

class Intersection
{
	public:
		Intersection(const Shape& shape, const Point& point);

		const Shape& shape() const;
		const Point& point() const;

	private:
		const Shape _shape;
		const Point _point;
};

