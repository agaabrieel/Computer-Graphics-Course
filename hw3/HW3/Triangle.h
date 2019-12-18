#pragma once
#include "Shape.h"

class Triangle :
	public Shape
{
	public:
		Triangle(Color diffuse, Color specular, float shininess, Color emission, Color ambient, 
			glm::mat4 transform, Point a, Point b, Point c);
		
		std::optional<Intersection> intersect(const Ray& ray) const;

	private:
		Point _a;
		Point _b;
		Point _c;

		Vector3 _normal_with_transform;
		Vector3 _normal_without_transform;

};

