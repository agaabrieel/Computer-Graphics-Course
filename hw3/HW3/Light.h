#pragma once
#include "Color.h"
#include "Point.h"

class Scene;

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

class Light  // abstract
{
	public:
		

		Light(Color color, Attenuation attenuation);

		Color color() const;
		Attenuation attenuation() const;
		
		virtual bool isVisibleFrom(Point point, const Scene* scene) const = 0; // returns true if there is an unobstructed path from the given point to the light.

		

	private:
		const Color _color;
		const Attenuation _attenuation;
};

