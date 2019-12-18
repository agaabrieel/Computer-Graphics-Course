#pragma once
#include "Light.h"
#include "Point.h"

class PointLight :
	public Light
{
	public:
		PointLight(Color color, Attenuation attenuation, Point point);

		Point point() const;

		bool isVisibleFrom(Point point, const Scene * scene) const;

	private: 
		const Point _point;
};

