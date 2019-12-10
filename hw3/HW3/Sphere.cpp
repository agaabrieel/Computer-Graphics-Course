#include "Sphere.h"

Sphere::Sphere(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform, Point center, float radius) :
	Shape(diffuse, specular, shininess, emission, ambient), _center(center), _radius(radius),
	_transform(transform),
	_transform_inverse(glm::inverse(_transform)) {}

Sphere::~Sphere()
{
}

Point Sphere::center() const { return _center; }

float Sphere::radius() const {	return _radius; }

glm::mat4 Sphere::transform() const { return _transform; }

std::optional<DistanceAndNormal> Sphere::intersect(Ray ray) const 
{
	// Transform ray to object coordinates.
	// Do sphere-ray' intersection to get p'
	Ray ray_prime = ray.toObjectCoordinates(_transform_inverse);

	// TODO: kludge using glm, later on we can define own operations on custom data types
	glm::vec3 p0_prime = ray_prime.origin().toGlmVec3();
	glm::vec3 p1_prime = ray_prime.direction().toGlmVec3();

	glm::vec3 center = _center.toGlmVec3();

	glm::vec3 p0_prime_minus_c = p0_prime - center;

	// Set up quadratic equation with coefficients a, b, c
	float a = glm::dot(p1_prime, p1_prime);
	float b = glm::dot(2.0f *  p1_prime, p0_prime_minus_c);
	float c = glm::dot(p0_prime_minus_c, p0_prime_minus_c) - (_radius * _radius);

	float discriminant = b * b - (4.0f * a * c);

	// Only complex roots
	if (discriminant < 0) {
		return std::nullopt;
	}

	float discriminant_sqrt = sqrt(discriminant);
	float denominator = (2.0f * a);

	float t_root_one = (-b + discriminant_sqrt) / denominator;
	float t_root_two = (-b - discriminant_sqrt) / denominator;

	float smallest_positive_root;

	if (t_root_one == t_root_two) {
		// Treat the case where the ray is exactly tangent to the sphere as no intersection.
		return std::nullopt;
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
		return std::nullopt;
	}

	glm::vec4 p_prime = glm::vec4(p0_prime + smallest_positive_root * p1_prime, 1);
	glm::vec4 normal_prime = p_prime - glm::vec4(center, 1);
	glm::vec4 normal4 = glm::transpose(_transform_inverse) * normal_prime;
	glm::vec3 normal = glm::vec3(normal4.x, normal4.y, normal4.z);
	normal = glm::normalize(normal);
	glm::vec4 p = _transform * p_prime;

	glm::vec3 p3 = glm::vec3(p.x / p.w, p.y / p.w, p.z / p.w);
	//glm::vec3 normal = p3 - center;
	//normal = glm::normalize(normal);
	// Transform p' back to p
	// p' = p0' + t' * p1'
	// p = Mp'

	// TODO we need to compute and return the surface normal

	return { {glm::distance(p, ray.origin().toGlmVec4()), normal} };
}