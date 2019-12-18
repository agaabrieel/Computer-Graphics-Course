#pragma once
#include "Point.h"

class Ray
{
	public:
		Ray(Point origin, Vector3 direction);
		Ray(glm::vec3 origin, glm::vec3 direction);
		
		Point origin() const;
		Vector3 direction() const;

		Ray toObjectCoordinates(const glm::mat4& m_inverse);

	private:
		const Point _origin;
		const Vector3 _direction;
};

