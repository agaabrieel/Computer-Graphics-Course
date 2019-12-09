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
		~DirectionalLight();

		Direction direction() const;

		bool isVisibleFrom(Point point) const;

	private:
		const Direction _direction;
};

