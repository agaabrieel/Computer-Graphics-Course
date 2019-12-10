#include "PointLight.h"
#include "Ray.h"
#include <optional>
#include "Intersection.h"
#include "Scene.h"

PointLight::PointLight(Color color, Attenuation attenuation, Point point) : Light(color, attenuation), _point(point) {}

PointLight::~PointLight()
{
}

Point PointLight::point() const { return _point; }

bool PointLight::isVisibleFrom(Point point, const Scene * scene) const
{
	glm::vec3 origin = point.toGlmVec3();
	glm::vec3 direction = _point.toGlmVec3() - origin;
	direction = glm::normalize(direction);

	origin += direction * 0.001f; // Bring origin of ray slightly towards light source to prevent self-intersection.

	Ray ray = Ray(origin, direction);
	std::optional<IntersectionAsStruct> t = std::nullopt;
	scene->intersect(ray, t);
	return !t.has_value();
}
