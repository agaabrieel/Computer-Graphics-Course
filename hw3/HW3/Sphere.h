#pragma once
#include "Shape.h"

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

