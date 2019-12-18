#pragma once
#include "Light.h"
#include "Point.h"

class PointLight :
	public Light
{
	public:
		PointLight(Color color, Attenuation attenuation, Point point);

		Point point() const;
		Attenuation attenuation() const;
		Vector3 directionFrom(const Point& point) const;
		Color computeContribution(Intersection hit_object, const Scene* scene) const;

	private: 
		const Point _point;
		const Attenuation _attenuation;
};

