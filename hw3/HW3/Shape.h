#pragma once

// Contains the class Shape, which will be subclassed by Sphere and Triangle

/* A shape has:

material properties:

diffuse (r, g, b)
specular (r, g, b)
shininess s
emission (r, g, b)

ambient (r, g, b) (possibly null, overrides the scene ambient lighting)

transform -> a matrix describing the transforms applied to it

*/




class Shape
{
	public:
		Shape(Color diffuse, Color specular, float shininess, Color emission, Color ambient, mat4 transform);

	private:
		Color diffuse;
		Color specular;
		float shininess;
		Color emission;
		Color ambient; // Maybe null

		mat4 transform;
};

