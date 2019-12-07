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

class Shape
{
	public:
		Shape(const Color& diffuse, const Color& specular, float shininess, const Color& emission, const Color& ambient, const glm::mat4& transform);
		~Shape();

		// Getters
		Color& diffuse() const; // We may not need to provide these public getters: maybe there is a way to do the shading by asking the shape to do it?
		Color& specular() const;		// Otherwise we are passing a lot of information around.
		float shininess() const;
		Color& emission() const;
		Color& ambient() const;
		glm::mat4& transform() const; // Is this the best name for this? It's the name from the previous project, but it's not very clear.
															// Maybe something like: worldToObject?

		Point* intersect(Ray ray) const;
			// determines the intersection point of the given object with the ray, if any
			// Presumably, uses world coordinates to determine the intersection?
			// Returns the location of the hit, or a null pointer if there is no valid intersection

	private:
		const Color _diffuse;
		const Color _specular;
		const float _shininess;
		const Color _emission;
		const Color _ambient; // Maybe null. How to model this? Since the lighting model is additive, one option is maybe (0, 0, 0)

		const glm::mat4 _transform;
};

