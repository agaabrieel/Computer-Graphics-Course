#include "Point.h"

Point::Point(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Point::Point(glm::vec3 p) : _x(p.x), _y(p.y), _z(p.z) {}

Point::Point(glm::vec4 p) : _x(p.x / p.w), _y(p.y / p.w), _z(p.z / p.w)
{
}

Point::~Point()
{
}

float Point::x() const { return _x; }

float Point::y() const { return _y; }

float Point::z() const { return _z; }

glm::vec3 Point::toGlmVec3() const
{
	return glm::vec3(_x, _y, _z);
}

glm::vec4 Point::toGlmVec4() const
{
	return glm::vec4(_x, _y, _z, 1);
}
