#pragma once
#include "Light.h"
#include "Vector3.h"


/*
A DirectionalLight also has:

direction (x, y, z)

*/

class DirectionalLight :
	public Light
{
	public:
		DirectionalLight(Color color, Attenuation attenuation, Vector3 direction);

		Vector3 direction() const;

		bool isVisibleFrom(Point point, const Scene* scene) const;

	private:
		const Vector3 _direction;
};

