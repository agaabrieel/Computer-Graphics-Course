#pragma once
#include "Point.h"
#include "Direction.h"

// Contains class/struct? to describe the camera. May not be necessary and could be contained in Scene.cpp instead.

/*
A Camera has:

lookfrom (x, y, z)
lookat (x, y, z)
up (x, y, z)
fovy (angle in radians (?))

*/


class Camera
{
	public:
		Camera(Point lookfrom, Point lookat, Direction up, float fovy_radians);

	private:
		Point lookfrom;
		Point lookat;
		Direction up;
		float fovy_radians;
};

