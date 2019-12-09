#pragma once

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>

// Vertex struct

// We can bring all these small files together into a header file such as utilities but for now I'll keep them separate

/*
A Vertex has:

x
y
z

(maybe pass through to glm::vec3)
*/

class Vertex
{
	public:
		Vertex(float x, float y, float z);
		~Vertex();

		float x() const;
		float y() const;
		float z() const;

		glm::vec3 toGlmVec3() const;

	private:
		const float _x;
		const float _y;
		const float _z;
};

