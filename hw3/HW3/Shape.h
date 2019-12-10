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
#include "Ray.h"
#include <optional>

class Shape  // abstract
{
	public:
		~Shape();

		// Getters
		Color diffuse() const; // We may not need to provide these public getters: maybe there is a way to do the shading by asking the shape to do it?
		Color specular() const;		// Otherwise we are passing a lot of information around.
		float shininess() const;
		Color emission() const;
		Color ambient() const;

		virtual std::optional<float> intersect(Ray ray) const = 0;
			// Returns the parameter t:
				// For now, return the smallest positive t if there is an intersection
				// Otherwise, return a negative number for no intersection
				// Later on, we can use boost::maybe or exceptions to handle this better.

	protected:
		Shape(Color diffuse, Color specular, float shininess, Color emission, Color ambient);

		const Color _diffuse;
		const Color _specular;
		const float _shininess;
		const Color _emission;
		const Color _ambient; // Maybe null. How to model this? Since the lighting model is additive, one option is maybe (0, 0, 0)	
};

