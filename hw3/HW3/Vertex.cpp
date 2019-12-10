#include "Vertex.h"

Vertex::Vertex(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vertex::Vertex(glm::vec4 homogeneous_coordinates) : 
	_x(homogeneous_coordinates.x / homogeneous_coordinates.w),
	_y(homogeneous_coordinates.y / homogeneous_coordinates.w),
	_z(homogeneous_coordinates.z / homogeneous_coordinates.w) {}


float Vertex::x() const { return _x; }

float Vertex::y() const { return _y; }

float Vertex::z() const { return _z; }

glm::vec3 Vertex::toGlmVec3() const
{
	return glm::vec3(_x, _y, _z);
}

glm::vec4 Vertex::toGlmVec4() const
{
	return glm::vec4(toGlmVec3(), 1);
}
