#include "Direction.h"
#include <math.h>
#include <stdexcept>

Direction::Direction(float x, float y, float z) : _x(x), _y(y), _z(z) {

	if (abs(x) < 0.0001 && abs(y) < 0.0001 && abs(z) < 0.0001) {
		throw std::out_of_range("Direction vector must not be the zero vector.");
	}

	normalise();
}


Direction::~Direction()
{
}

float Direction::x() const { return _x; }

float Direction::y() const { return _y; }

float Direction::z() const { return _z; }

void Direction::normalise()
{
	float magnitude = (float)sqrt(_x * (double)_x + _y * (double)_y + _z * (double)_z);
	_x = _x / magnitude;
	_y = _y / magnitude;
	_z = _z / magnitude;
}
