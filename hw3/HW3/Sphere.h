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

		glm::mat4 transform() const; // Is this the best name for this? It's the name from the previous project, but it's not very clear.
															// Maybe something like: worldToObject?

		std::optional<DistanceAndNormal> intersect(Ray ray) const;

	private:
		const Point _center;
		const float _radius; // TODO: consider storing radius squared since that is what seems to be needed.
		const glm::mat4 _transform;
		const glm::mat4 _transform_inverse; // Only needed by sphere, not triangle
};

