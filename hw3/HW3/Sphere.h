#pragma once
#include "Shape.h"
#include "Point.h"

/*
A sphere has:

center (x, y, z)
radius

*/


class Sphere :
	public Shape
{
	public:
		Sphere(Color diffuse, Color specular, float shininess, Color emission, Color ambient, 
			glm::mat4 transform, Point center, float radius);
		~Sphere();
		
		Point center() const;
		float radius() const;

		Point* intersect(Ray ray) const;

	private:
		const Point _center;
		const float _radius;
};

