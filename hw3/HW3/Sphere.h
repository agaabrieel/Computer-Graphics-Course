#pragma once
#include "Shape.h"
#include "Point.h"

class Sphere :
	public Shape
{
	public:
		Sphere(Color diffuse, Color specular, float shininess, Color emission, Color ambient, 
			glm::mat4 transform, Point center, float radius);
		
		Point center() const;
		float radius_squared() const;

		std::optional<Intersection> intersect(const Ray& ray) const;

	private:
		const Point _center;
		const float _radius_squared;
		const glm::mat4 _transform;
		const glm::mat4 _transform_inverse; 
};

