#pragma once
#include "Light.h"
#include "Direction.h"


/*
A DirectionalLight also has:

direction (x, y, z)

*/

class DirectionalLight :
	public Light
{
	public:
		DirectionalLight(const Color& color, const Attenuation& attenuation, const Direction& direction);

		Direction& direction() const;

	private:
		const Direction _direction;
};

