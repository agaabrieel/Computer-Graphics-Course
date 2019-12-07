#pragma once

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

		float x() const;
		float y() const;
		float z() const;

	private:
		const float _x;
		const float _y;
		const float _z;
};

