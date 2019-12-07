#include "Intersection.h"

Intersection::Intersection(Shape* shape, Point point) : _shape(shape), _point(point) {}

Intersection::~Intersection()
{
}

const Shape* Intersection::shape() const { return _shape; }

const Point Intersection::point() const { return _point; }
