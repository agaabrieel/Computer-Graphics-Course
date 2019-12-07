#pragma once
#include <stack>
#include <glm\detail\type_mat.hpp>  // Maybe use the more general kind?

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
		MatrixStack(); // Do we start with identity

		glm::mat4& top();

		void pushTransform();
		void popTransform();

		void rightMultiplyTopOfStack(glm::mat4& M);

	private:
		const std::stack<glm::mat4> _transformationStack;
};

