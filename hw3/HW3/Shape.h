#pragma once
#include "Color.h"

// Contains the class Shape, which will be subclassed by Sphere and Triangle

/* A shape has:

material properties:

diffuse (r, g, b)
specular (r, g, b)
shininess s
emission (r, g, b)

ambient (r, g, b) (possibly null, overrides the scene ambient lighting)

transform -> a matrix describing the transforms applied to it

A Shape can:
// Intersect(Ray)
	// determines the intersection point of the given object with the ray, if any

*/

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>

class Shape
{
	public:
		Shape(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform);

	private:
		Color diffuse;
		Color specular;
		float shininess;
		Color emission;
		Color ambient; // Maybe null

		glm::mat4 transform;
};

