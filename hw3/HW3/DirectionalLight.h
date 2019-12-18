#pragma once
#include "Light.h"
#include "Vector3.h"


class DirectionalLight :
	public Light
{
	public:
		DirectionalLight(Color color, Vector3 direction);

		Vector3 direction() const;
		bool isVisibleFrom(Point point, const Scene* scene) const;

	private:
		const Vector3 _direction;
};

