#pragma once
#include "Color.h"
#include "Attenuation.h"
#include "Point.h"

/*
A light has

color (r, g, b)
attenuation (const, linear, quadratic)

*/

class Scene;

class Light  // abstract
{
	public:
		Light(Color color, Attenuation attenuation);
		~Light();
		Color color() const;
		Attenuation attenuation() const;
		
		virtual bool isVisibleFrom(Point point, const Scene* scene) const = 0; // returns true if there is an unobstructed path from the given point to the light.

		

	private:
		const Color _color;
		const Attenuation _attenuation;
};

