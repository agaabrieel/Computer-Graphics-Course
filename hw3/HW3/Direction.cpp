#include "Direction.h"
#include <math.h>
#include <stdexcept>

Direction::Direction(float x, float y, float z) : Vector(x, y, z) {

	if (abs(x) < 0.0001 && abs(y) < 0.0001 && abs(z) < 0.0001) {
		throw std::out_of_range("Direction vector must not be the zero vector.");
	}

	normalise();
}

Direction::Direction(glm::vec4 d) : Direction(d.x, d.y, d.z)
{
}


Direction::~Direction()
{
}

glm::vec4 Direction::toGlmVec4() const
{
	return glm::vec4(_x, _y, _z, 0); // No translation component for direction
}

void Direction::normalise()
{
	float magnitude = (float)sqrt(_x * (double)_x + _y * (double)_y + _z * (double)_z);
	_x = _x / magnitude;
	_y = _y / magnitude;
	_z = _z / magnitude;
}
