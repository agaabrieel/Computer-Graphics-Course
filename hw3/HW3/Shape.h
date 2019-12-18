#pragma once
#include "Color.h"
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include "Ray.h"
#include <optional>

struct DistanceAndNormal {
	float distance;
	Vector3 normal;
};

class Shape  // abstract
{
	public:
		// Getters
		Color diffuse() const; // We may not need to provide these public getters: maybe there is a way to do the shading by asking the shape to do it?
		Color specular() const;		// Otherwise we are passing a lot of information around.
		float shininess() const;
		Color emission() const;
		Color ambient() const;

		virtual std::optional<DistanceAndNormal> intersect(Ray ray) const = 0;

	protected:
		Shape(Color diffuse, Color specular, float shininess, Color emission, Color ambient);

		const Color _diffuse;
		const Color _specular;
		const float _shininess;
		const Color _emission;
		const Color _ambient;
};

