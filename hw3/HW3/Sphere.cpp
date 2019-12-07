#include "Sphere.h"

Sphere::Sphere(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform, Point center, float radius) :
	Shape(diffuse, specular, shininess, emission, ambient, transform), _center(center), _radius(radius) {}

Sphere::~Sphere()
{
}

Point Sphere::center() const { return _center; }

float Sphere::radius() const {	return _radius; }

Point* Sphere::intersect(Ray ray) const 
{
	return nullptr; // TODO
}