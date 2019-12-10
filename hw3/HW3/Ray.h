#pragma once
#include "Point.h"
#include "Direction.h"

/*
A ray has:

An Origin (Point)
A Direction

*/


class Ray
{
	public:
		Ray(Point origin, Direction direction);
		Ray(glm::vec3 origin, glm::vec3 direction);
		~Ray();
		
		Point origin() const;
		Direction direction() const;

		Ray toObjectCoordinates(const glm::mat4& m_inverse);

	private:
		const Point _origin;
		const Direction _direction;
};

