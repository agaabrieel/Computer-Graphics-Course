#include "Ray.h"

Ray::Ray(Point origin, Direction direction) : _origin(origin), _direction(direction) {}

Ray::~Ray()
{
}

Point Ray::origin() const {	return _origin; }

Direction Ray::direction() const { return _direction; }
