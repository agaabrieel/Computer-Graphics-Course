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
		Intersection(Shape* shape, Point point);
		Intersection(const Intersection& i2);
		~Intersection();

		Shape* shape();
		Point point() const;

	private:
		Shape* _shape;
		const Point _point;
};

