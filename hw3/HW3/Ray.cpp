#include "Ray.h"

Ray::Ray(Point origin, Direction direction) : _origin(origin), _direction(direction) {}

Ray::Ray(glm::vec3 origin, glm::vec3 direction) :
	Ray(Point(origin.x, origin.y, origin.z), Direction(direction.x, direction.y, direction.z)) {}


Ray::~Ray()
{
}

Point Ray::origin() const {	return _origin; }

Direction Ray::direction() const { return _direction; }

Ray Ray::toObjectCoordinates(const glm::mat4& m_inverse)
{
	Point origin_prime = Point(m_inverse * _origin.toGlmVec4());
	Direction direction_prime = Direction(m_inverse * _direction.toGlmVec4());
	return Ray(origin_prime, direction_prime);
}

