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
		Sphere(const Color& diffuse, const Color& specular, float shininess, const Color& emission, const Color& ambient, 
			const glm::mat4& transform, const Point& center, float radius);
		~Sphere();
		
		Point& center() const;
		float radius() const;

	private:
		const Point _center;
		const float _radius;
};

