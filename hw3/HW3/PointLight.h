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
		PointLight(Color color, Attenuation attenuation, Point point);
		~PointLight();

		Point point() const;

		bool isVisibleFrom(Point point, const Scene * scene) const;

	private: 
		const Point _point;
};

