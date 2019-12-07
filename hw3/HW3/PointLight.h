#pragma once
#include "Light.h"
#include "Point.h"


/*
A PointLight also has:

Point (x, y, z)

*/

class PointLight :
	public Light
{
	public:
		PointLight(const Color& color, const Attenuation& attenuation, const Point& point);

		Point& point() const;

	private: 
		const Point _point;
};

