#include "PointLight.h"
#include "Ray.h"
#include <optional>
#include "Scene.h"

PointLight::PointLight(Color color, Attenuation attenuation, Point point) : Light(color), _point(point), _attenuation(attenuation) {}

Point PointLight::point() const { return _point; }
Attenuation PointLight::attenuation() const { return _attenuation; }

bool PointLight::isVisibleFrom(Point object_location, const Scene * scene) const
{
	Vector3 shadow_ray_direction = _point - object_location;
	shadow_ray_direction = shadow_ray_direction.normalize();

	// Bring origin of ray slightly towards light source to prevent self-intersection.
	Point shadow_ray_origin = object_location + shadow_ray_direction * 0.001f; 

	Ray shadow_ray = Ray(shadow_ray_origin, shadow_ray_direction);
	std::optional<Intersection> intersection = scene->intersect(shadow_ray);
	
	if (!intersection.has_value()) {
		return true; // No object intersects on this ray.
	}

	// The distance to the light is smaller than the distance to the first object intersection, so the light is visible
	return object_location.distanceTo(_point) < intersection.value().distance;

}
