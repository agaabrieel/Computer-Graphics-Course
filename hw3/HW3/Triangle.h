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
		Triangle(const Color& diffuse, const Color& specular, float shininess, const Color& emission, const Color& ambient, 
			const glm::mat4& transform, const Vertex& a, const Vertex& b, const Vertex& c);
		~Triangle();

		Vertex& a() const;
		Vertex& b() const;
		Vertex& c() const;

	private:
		const Vertex _a;
		const Vertex _b;
		const Vertex _c;

};

