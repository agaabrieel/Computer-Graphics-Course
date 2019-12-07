#pragma once
#include <stack>
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>

/*
A Matrix Stack has:

a stack of matrices

A MatrixStack can:

give you the top of the stack
duplicate the top of the stack push(top)
pop the top of the stack

right multiply the top of the stack

*/

class MatrixStack
{
	public:
		MatrixStack(); // Do we start with identity?

		glm::mat4& top();

		void pushTransform();
		void popTransform();

		void rightMultiplyTopOfStack(glm::mat4& M);

	private:
		const std::stack<glm::mat4> _transformationStack;
};

