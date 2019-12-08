#include "Vector.h"

Vector::Vector(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vector::~Vector()
{
}

float Vector::x() const { return _x; }

float Vector::y() const { return _y; }

float Vector::z() const { return _z; }
