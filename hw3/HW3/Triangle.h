#pragma once
#include "Shape.h"
#include "Vertex.h"


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
	public:
		Triangle(Color diffuse, Color specular, float shininess, Color emission, Color ambient, 
			glm::mat4 transform, Vertex a, Vertex b, Vertex c);
		~Triangle();
		
		float intersect(Ray ray) const;

	private:
		const Vertex _a;
		const Vertex _b;
		const Vertex _c;

};

