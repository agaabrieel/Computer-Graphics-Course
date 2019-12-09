#include "Sphere.h"

Sphere::Sphere(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform, Point center, float radius) :
	Shape(diffuse, specular, shininess, emission, ambient, transform), _center(center), _radius(radius) {}

Sphere::~Sphere()
{
}

Point Sphere::center() const { return _center; }

float Sphere::radius() const {	return _radius; }

float Sphere::intersect(Ray ray) const 
{
	// TODO: kludge using glm, later on we can define own operations on custom data types
	glm::vec3 p0 = ray.origin().toGlmVec3();
	glm::vec3 p1 = ray.direction().toGlmVec3();

	glm::vec3 center = _center.toGlmVec3();

	glm::vec3 p0_minus_c = p0 - center;

	// Set up quadratic equation with coefficients a, b, c
	float a = glm::dot(p1, p1);
	float b = 2.0f * glm::dot(p1, p1 - center);
	float c = glm::dot(p0_minus_c, p0_minus_c) - (_radius * _radius);

	float discriminant = b * b - (4.0 * a * c);

	// Only complex roots
	if (discriminant < 0) {
		return -1.0f;
	}

	float discriminant_sqrt = sqrt(discriminant);
	float denominator = (2.0f * a);

	float t_root_one = (-b + discriminant_sqrt) / denominator;
	float t_root_two = (-b - discriminant_sqrt) / denominator;

	float smallest_positive_root;

	if (t_root_one == t_root_two) {
		// Treat the case where the ray is exactly tangent to the sphere as no intersection.
		return -1.0f;
	}

	// Two positive roots, choose smallest
	if (t_root_one > 0 && t_root_two > 0) {
		smallest_positive_root = glm::min(t_root_one, t_root_two);
	}
	else if (t_root_one > 0) {
		smallest_positive_root = t_root_one;
	}
	else if (t_root_two > 0) {
		smallest_positive_root = t_root_two;
	}
	else {
		// Shouldn't reach this case since we checked the discriminant
		return -1.0f;
	}

	return smallest_positive_root;
}