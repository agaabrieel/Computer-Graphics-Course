#include "Direction.h"

Direction::Direction(float x, float y, float z) : _x(x), _y(y), _z(z) {}  // TODO: forbid zero vector, auto-normalise on store

Direction::~Direction()
{
}

float Direction::x() const { return _x; }

float Direction::y() const { return _y; }

float Direction::z() const { return _z; }

void Direction::normalise()
{
	// TODO
}
