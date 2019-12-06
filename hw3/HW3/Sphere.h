#pragma once
#include "Shape.h"
#include "Point.h"

/*
A sphere has:

center (x, y, z)
radius

*/


class Sphere :
	public Shape
{
	private:
		Point center;
		float radius;
};

