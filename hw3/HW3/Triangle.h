#pragma once
#include "Shape.h"


/*
A triangle has:

vertexA
vertexB
vertexC

vertices are in counterclockwise order

a vertex is (x, y, z)

*/

class Triangle :
	public Shape
{
	private:
		Vertex a;
		Vertex b;
		Vertex c;

};

