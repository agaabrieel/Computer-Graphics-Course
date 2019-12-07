#pragma once
#include "Color.h"
#include "Attenuation.h"

/*
A light has

color (r, g, b)
attenuation (const, linear, quadratic)

*/

class Light  // abstract
{
	public:
		Color color() const;
		Attenuation attenuation() const;
		virtual ~Light() = 0;

	protected:
		Light(Color color, Attenuation attenuation);

	private:
		const Color _color;
		const Attenuation _attenuation;
};

