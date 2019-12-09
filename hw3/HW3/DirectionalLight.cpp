#include "DirectionalLight.h"
#include "Ray.h"
#include <optional>
#include "Scene.h"

DirectionalLight::DirectionalLight(Color color, Attenuation attenuation, Direction direction) : 
	Light(color, attenuation), _direction(direction) {}

DirectionalLight::~DirectionalLight()
{
}

Direction DirectionalLight::direction() const {	return _direction; }

bool DirectionalLight::isVisibleFrom(Point point, Scene* scene) const 
{
	glm::vec3 origin = point.toGlmVec3();
	glm::vec3 direction = _direction.toGlmVec3();
	direction = glm::normalize(direction);

	origin += direction * 0.001f; // Bring origin of ray slightly towards light source to prevent self-intersection.

	Ray ray = Ray(origin, direction);
	std::optional<IntersectionAsStruct> t = std::nullopt;
	scene->intersect(ray, t);
	return !t.has_value();
}
