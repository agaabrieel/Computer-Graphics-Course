#pragma once
#include "Point.h"

class Camera
{
	public:
		Camera(Point lookfrom, Point lookat, Vector3 up, float fovy_radians);

		Point lookfrom() const;
		Point lookat() const;
		Vector3 up() const;
		float fovy_radians() const;

	private:
		const Point _lookfrom;
		const Point _lookat;
		const Vector3 _up;
		const float _fovy_radians;
};

