// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	float rads = glm::radians(degrees);
	float cos_rads = cos(rads);
	mat3 a_star = mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);

	return cos_rads * mat3() + (1 - cos_rads) * glm::outerProduct(axis, axis) + sin(rads) * a_star;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	vec3 rotation_axis = glm::normalize(glm::cross(eye, up));
	mat3 rotation_matrix = rotate(degrees, rotation_axis);

	eye = rotation_matrix * eye;
	up = glm::normalize(rotation_matrix * up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3 a = eye - center; // TODO check this use of center is appropriate.
	vec3 b = up;

	vec3 w = glm::normalize(a);
	vec3 u = glm::cross(b, w);
	u = glm::normalize(u);
	vec3 v = glm::cross(w, u);

	mat4 m;

	// Row 1
	m[0][0] = u.x;
	m[0][1] = u.y;
	m[0][2] = u.z;
	m[0][3] = -glm::dot(u, eye);

	// Row 2
	m[1][0] = v.x;
	m[1][1] = v.y;
	m[1][2] = v.z;
	m[1][3] = -glm::dot(v, eye);

	// Row 3
	m[2][0] = w.x;
	m[2][1] = w.y;
	m[2][2] = w.z;
	m[2][3] = -glm::dot(w, eye);

	// Row 4
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;

	return glm::transpose(m);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
