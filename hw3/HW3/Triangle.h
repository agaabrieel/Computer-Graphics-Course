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
		
		std::optional<DistanceAndNormal> intersect(Ray ray) const;

		glm::vec3 normal() const;

	private:
		Vertex _a;
		Vertex _b;
		Vertex _c;

		glm::vec3 _a_glm; // TODO: provided at the moment for ease of computation of the normal. Later on we can remove these
							// when we add more functionality to the custom classes
		glm::vec3 _b_glm;
		glm::vec3 _c_glm;

		glm::vec3 _normal_with_transform;
		glm::vec3 _normal_without_transform;

};

