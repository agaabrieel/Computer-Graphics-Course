#include "Triangle.h"

Triangle::Triangle(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform, Vertex a, Vertex b, Vertex c) :
	Shape(diffuse, specular, shininess, emission, ambient),
	_a(Vertex(transform * a.toGlmVec4())), // Transform vertexes to eye coordinates
	_b(Vertex(transform * b.toGlmVec4())),
	_c(Vertex(transform * c.toGlmVec4()))
{
	_a_glm = _a.toGlmVec3();
	_b_glm = _b.toGlmVec3();
	_c_glm = _c.toGlmVec3();

	_normal_with_transform = glm::cross(_c_glm - _a_glm, _b_glm - _a_glm);
	_normal_with_transform = glm::normalize(_normal_with_transform);

	_normal_without_transform = glm::cross(c.toGlmVec3() - a.toGlmVec3(), b.toGlmVec3() - a.toGlmVec3());
	_normal_without_transform = glm::normalize(_normal_without_transform);
}

Triangle::~Triangle()
{
}

std::optional<DistanceAndNormal> Triangle::intersect(Ray ray) const
{
	// Triangles are stored with the transform already applied to the vertexes, so we do not need to worry about transforms here.
	// Begin ray-plane intersection
		
	glm::vec3 p0 = ray.origin().toGlmVec3();
	glm::vec3 p1 = ray.direction().toGlmVec3();
	
	float denominator = glm::dot(p1, _normal_with_transform);

	// No intersection when parallel to the plane
	if (denominator == 0.0f) { // TODO: might we allow a small tolerance here for floating point error?
		return std::nullopt;
	}

	float t = (glm::dot(_a_glm, _normal_with_transform) - glm::dot(p0, _normal_with_transform)) / denominator;
	
	// The ray intersects the plane in the negative direction.
	if (t <= 0) {
		return std::nullopt;
	}

	
	// End ray-plane intersection
	/*
	Vector v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = Dot(v0, v0);
    float d01 = Dot(v0, v1);
    float d11 = Dot(v1, v1);
    float d20 = Dot(v2, v0);
    float d21 = Dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
	*/

	// Begin compute barycentric coordinates.
		// From https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
		// Later on, can use custom algorithm, but this will do for now.
	glm::vec3 p = p0 + t * p1;
	glm::vec3 v0 = _b_glm - _a_glm;
	glm::vec3 v1 = _c_glm - _a_glm;
	glm::vec3 v2 = p - _a_glm;

	float d00 = glm::dot(v0, v0);
	float d01 = glm::dot(v0, v1);
	float d11 = glm::dot(v1, v1);
	float d20 = glm::dot(v2, v0);
	float d21 = glm::dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;
	float beta = (d11 * d20 - d01 * d21) / denom;
	float gamma = (d00 * d21 - d01 * d20) / denom;
	float alpha = 1.0f - beta - gamma;
	// End compute barycentric coordinates.

	// TODO: we need to compute and return the surface normal


	if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
		return { {t, -_normal_with_transform } }; // TODO negating the normal fixes the problem with lighting for triangles, but really we should address why the normal is facing the wrong way.
	}
	else {
		return std::nullopt;
	}
}

glm::vec3 Triangle::normal() const { return _normal_with_transform; }
