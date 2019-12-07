#pragma once
#include <stack>
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>
#include "Direction.h"

/*
A Transform Stack has:

a stack of matrices

A TransformStack can:

give you the top of the stack (a matrix)
duplicate the top of the stack push(top) to set up new transforms
pop the top of the stack to get rid of the last group of transforms

rotate the top matrix
translate the top matrix
scale the top matrix

// Scale(sx, sy, sz)
	// Returns a matrix that will scale the view

// Translate(tx, ty, tz)
	// Returns a matrix that will translate the view

// Rotate(rx, ry, rz)
	// Returns a matrix that will rotate the view

	// Transformations are applied to the top matrix in the stack.

*/

class TransformStack
{
	public:
		TransformStack(); // Do we start with identity?

		glm::mat4& top();

		void pushTransform();
		void popTransform();

		void scale(float sx, float sy, float sz);
		void translate(float tx, float ty, float tz);
		void rotate(const float degrees, const Direction& axis);

	private:
		const std::stack<glm::mat4> _transformationStack;
};

