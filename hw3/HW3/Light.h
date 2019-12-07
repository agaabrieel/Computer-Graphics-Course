#pragma once
#include "Color.h"
#include "Attenuation.h"

/*
A light has

color (r, g, b)
attenuation (const, linear, quadratic)

*/

class Light  // This class should be abstract, but I can deal with that later.
{
	public:
		~Light();

	protected:
		Light(Color color, Attenuation attenuation);

		Color color() const;
		Attenuation attenuation() const;

	private:
		const Color _color;
		const Attenuation _attenuation;
};

