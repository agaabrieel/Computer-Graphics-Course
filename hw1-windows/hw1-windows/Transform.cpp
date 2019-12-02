// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <iostream>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  
	float rads = glm::radians(degrees);
	float cos_rads = cos(rads);
	mat3 a_star = mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);
	
	return cos_rads * mat3() + (1 - cos_rads) * glm::outerProduct(axis, axis) + sin(rads) * a_star;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {

	eye = rotate(degrees, up) * eye;
}


// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {

	vec3 rotation_axis = glm::normalize(glm::cross(eye, up));
	mat3 rotation_matrix = rotate(degrees, rotation_axis);

	eye = rotation_matrix * eye;
	up = glm::normalize(rotation_matrix * up);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  
	vec3 center = vec3(0, 0, 0);

	vec3 a = eye - center;
	vec3 b = up;

	vec3 w = glm::normalize(a);
	vec3 u = glm::cross(b, w);
	u = glm::normalize(u);
	vec3 v = glm::cross(w, u);

	mat4 m;
	
	m[0][0] = u.x;
	m[0][1] = u.y;
	m[0][2] = u.z;
	m[0][3] = -glm::dot(u, eye);

	m[1][0] = v.x;
	m[1][1] = v.y;
	m[1][2] = v.z;
	m[1][3] = -glm::dot(v, eye);

	m[2][0] = w.x;
	m[2][1] = w.y;
	m[2][2] = w.z;
	m[2][3] = -glm::dot(w, eye);

	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

	return glm::transpose(m);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}