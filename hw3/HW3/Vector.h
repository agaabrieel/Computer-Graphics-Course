#pragma once

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>

class Vector
{
	public:
		Vector(float x, float y, float z);
		~Vector();

		float x() const;
		float y() const;
		float z() const;

		glm::vec3 toGlmVec3() const;

	protected:
		float _x;
		float _y;
		float _z;
};

