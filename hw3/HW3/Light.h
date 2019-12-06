#pragma once
#include "Color.h"

/*
A light has

color (r, g, b)
attenuation (const, linear, quadratic)

*/

class Light
{

	private:
		Color color;
		float attenuation_constant; // TODO define struct for attenuation
		float attenuation_linear;
		float attenuation_quadratic;
};

