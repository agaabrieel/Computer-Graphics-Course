#include "DirectionalLight.h"
#include "Ray.h"
#include <optional>
#include "Scene.h"

DirectionalLight::DirectionalLight(Color color, Vector3 direction) : 
	Light(color), _direction(direction.normalize()) {}

Vector3 DirectionalLight::direction() const {	return _direction; }

bool DirectionalLight::isVisibleFrom(Point point, const Scene* scene) const 
{
	glm::vec3 origin = point.toGlmVec3();
	glm::vec3 direction = _direction.toGlmVec3();
	direction = glm::normalize(direction);

	origin += direction * 0.001f; // Bring origin of ray slightly towards light source to prevent self-intersection.

	Ray ray = Ray(origin, direction);
	std::optional<Intersection> t = scene->intersect(ray);

	// Any object in the direction will be obstructing the directional light, since the light is at a point at infinity.
	return !t.has_value();
}
