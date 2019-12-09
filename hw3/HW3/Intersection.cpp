#include "Intersection.h"

Intersection::Intersection(Shape* shape, Point point) : _shape(shape), _point(point) {}

Intersection::Intersection(const Intersection& i2) : _shape(i2._shape), _point(i2._point) {}

Intersection::~Intersection()
{
}

Shape* Intersection::shape() { return _shape; }

Point Intersection::point() const { return _point; }
