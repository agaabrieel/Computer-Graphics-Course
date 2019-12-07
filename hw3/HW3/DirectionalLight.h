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
		DirectionalLight(Color color, Attenuation attenuation, Direction direction);

		Direction& direction() const;

	private:
		const Direction _direction;
};

