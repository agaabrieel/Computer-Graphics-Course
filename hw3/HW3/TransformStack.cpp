#include "TransformStack.h"

TransformStack::TransformStack()
{
	_transformationStack = std::stack<glm::mat4>();
	_transformationStack.push(glm::mat4()); // Start with identity
}

TransformStack::~TransformStack()
{
}

glm::mat4& TransformStack::top()
{
	return _transformationStack.top();
}

void TransformStack::pushTransform()
{
	_transformationStack.push(_transformationStack.top());
}

void TransformStack::popTransform()
{
	_transformationStack.pop(); // TODO: prevent popping empty stack, should always have identity?
}

void TransformStack::scale(float sx, float sy, float sz)
{
	// TODO
}

void TransformStack::translate(float tx, float ty, float tz)
{
	//TODO
}

void TransformStack::rotate(float angle_radians, const Direction& axis)
{
	// TODO
}
