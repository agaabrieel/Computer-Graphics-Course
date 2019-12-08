#include "Triangle.h"

Triangle::Triangle(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform, Vertex a, Vertex b, Vertex c) :
	Shape(diffuse, specular, shininess, emission, ambient, transform), _a(a), _b(b), _c(c) {}

Triangle::~Triangle()
{
}

Point* Triangle::intersect(Ray ray) const
{
	return nullptr; //TODO
}