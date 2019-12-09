#include "Triangle.h"

Triangle::Triangle(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform, Vertex a, Vertex b, Vertex c) :
	Shape(diffuse, specular, shininess, emission, ambient, transform), _a(a), _b(b), _c(c) {}

Triangle::~Triangle()
{
}

float Triangle::intersect(Ray ray) const
{
	glm::vec3 A = _a.toGlmVec3();
	glm::vec3 B = _b.toGlmVec3();
	glm::vec3 C = _c.toGlmVec3();

	glm::vec3 normal = glm::cross(C - A, B - A);
	normal = glm::normalize(normal);
	
	glm::vec3 p0 = ray.origin().toGlmVec3();
	glm::vec3 p1 = ray.direction().toGlmVec3();

	float denominator = glm::dot(p1, normal);

	// No intersection when parallel to the plane
	if (denominator == 0.0f) { // TODO: might we allow a small tolerance here for floating point error?
		return -1.0f;
	}

	float t = (glm::dot(A, normal) - glm::dot(p0, normal)) / denominator;

	return t;
}