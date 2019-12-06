#pragma once
#include "Color.h"
#include "Attenuation.h"

/*
A light has

color (r, g, b)
attenuation (const, linear, quadratic)

*/

class Light
{
	public:
		Light(Color color, Attenuation attenuation);

	private:
		const Color color;
		const Attenuation attenuation;
};

