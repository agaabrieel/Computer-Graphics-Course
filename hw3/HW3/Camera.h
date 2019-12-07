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
		Camera(const Point& lookfrom, const Point& lookat, const Direction& up, float fovy_radians);
		~Camera();

		Point& lookfrom() const;
		Point& lookat() const;
		Direction& up() const;
		float fovy_radians() const;

	private:
		const Point _lookfrom;
		const Point _lookat;
		const Direction _up;
		const float _fovy_radians;
};

