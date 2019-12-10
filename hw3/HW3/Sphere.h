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

		std::optional<float> intersect(Ray ray) const;

	private:
		const Point _center;
		const float _radius; // TODO: consider storing radius squared since that is what seems to be needed.
		const glm::mat4 _transform_inverse; // Only needed by sphere, not triangle
};

