#include "Triangle.h"

Triangle::Triangle(Color diffuse, Color specular, float shininess, Color emission, Color ambient, glm::mat4 transform, Point a, Point b, Point c) :
	Shape(diffuse, specular, shininess, emission, ambient),
	_a(Point(transform * a.toGlmVec4())), // Transform vertexes to eye coordinates
	_b(Point(transform * b.toGlmVec4())),
	_c(Point(transform * c.toGlmVec4()))
{
	_normal_with_transform = (_c - _a).cross(_b - _a);
	_normal_with_transform = _normal_with_transform.normalize();

	_normal_without_transform = (c - a).cross(b - a);
	_normal_without_transform = _normal_without_transform.normalize();
}


std::optional<Intersection> Triangle::intersect(const Ray& ray) const
{
	// Triangles are stored with the transform already applied to the vertexes, so we do not need to worry about transforms here.
	// Begin ray-plane intersection
	Point p0 = ray.origin();
	Vector3 p1 = ray.direction();
	
	float denominator = p1.dot(_normal_with_transform);

	// No intersection when parallel to the plane
	if (denominator == 0.0f) { // TODO: might we allow a small tolerance here for floating point error?
		return std::nullopt;
	}

	float t = (_a.asVector3().dot(_normal_with_transform) - p0.asVector3().dot(_normal_with_transform)) / denominator;
	
	// The ray intersects the plane in the negative direction.
	if (t <= 0) {
		return std::nullopt;
	}

	// Begin compute barycentric coordinates.
		// From https://gamedev.stackexchange.com/questions/23743/whats-the-most-efficient-way-to-find-barycentric-coordinates
		// TODO Later on, can use custom algorithm, but this will do for now.
	Point p = p0 + t * p1;
	Vector3 v0 = _b - _a;
	Vector3 v1 = _c - _a;
	Vector3 v2 = p - _a;

	float d00 = v0.dot(v0);
	float d01 = v0.dot(v1);
	float d11 = v1.dot(v1);
	float d20 = v2.dot(v0);
	float d21 = v2.dot(v1);
	float denom = d00 * d11 - d01 * d01;
	float beta = (d11 * d20 - d01 * d21) / denom;
	float gamma = (d00 * d21 - d01 * d20) / denom;
	float alpha = 1.0f - beta - gamma;
	// End compute barycentric coordinates.


	if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
		// TODO negating the normal fixes the problem with lighting for triangles, but really we should address why the normal is facing the wrong way.
		return { { this, p, -_normal_with_transform, ray, t } };
	}
	else {
		return std::nullopt;
	}
}

Vector3 Triangle::normal() const { return _normal_with_transform; }
