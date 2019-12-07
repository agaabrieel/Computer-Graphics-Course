#pragma once
#include <sstream>

namespace ReadFile {

	// From HW2
	bool readvals(std::stringstream& s, const int numvals, float* values); // Does this need to be GLfloat? Maybe it's a float[] ?
	void readfile(const char* filename);

}
// This file will contain the input file parser

// Commands still to parse:

/*
#comment - Just ignore
blank line - also ignore

need to have:
	list of vertexes (temporary, 0-indexed)
	Scene object
	Options struct
	Camera struct

	a temporary matrix stack, starting with the identity
	attentuation -> current value, starts at (1, 0, 0)
	ambient -> a Color, starts at (.2, .2, .2)
	diffuse -> a Color
	specular -> a Color
	shininess -> a float (?)
	emission -> a Color

commands:

size width height
	-> create the Scene object with this paramter (this is first command in file so we should be able to make sure this is initiliased before other things)

maxdepth depth
	-> store temporarily
	-> put in the Options struct at the end

output filename
	-> store temporarily
	-> put in the Options struct at the end

camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fovy
	-> make a Camera object/struct to store this

sphere x y z radius
	-> make a Sphere object with the current values for material properties
	-> add the Sphere to the scene

maxverts number
	-> ignore, we will allow arbitrary number of vertexes

maxvertnorms number
	-> ignore, this is optional
	-> we could add functionality later, but for now let's keep it simple

vertex x y z
	-> make a Vertex object and add it to the temporary list of objects. Indexing will be important, we need to know the order the vertexes are added,
		since that is how they are referred to in this file. They are 0-indexed

vertexnormal x y z nx ny nz
	-> ignore, this is optional
	-> we could add functionality later, but for now let's keep it simple

tri v1 v2 v3
	-> create a Triangle with the three vertices listed in the temporary vertex list at given indexes
	-> add the triangle to the Scene

trinormal
	-> ignore, this is optional
	-> we could add functionality later, but for now let's keep it simple

translate x y z
	-> get a translation matrix for the given values and right multiply it with the top of the matrix stack

rotate x y z angle
	-> get a rotation matrix for the given values and right multiply it with the top of the matrix stack

scale x y z
	-> get a scale matrix and right multiply it with the top of the stack

pushTransform
	-> add a copy of the top of the matrix stack to the top of the stack

popTransform
	-> check the matrix stack is not empty
	-> pop the top of the matrix stack

directional x y z r g b
	-> create a color from the r g b
	-> create a direction from the x y z
	-> create a DirectionalLight from these
	-> add the DirectionalLight to the scene

point x y z r g b
	-> create a color from the r g b
	-> create a Point from the x y z
	-> create a PointLight from these
	-> add the PointLight to the Scene

attenuation const linear quadractic
	-> update attenuation to have these values

ambient r g b
	-> make a Color with the r g b
	-> update ambient to this Color

diffuse r g b
	-> make a Color with the r g b
	-> update diffuse to this Color

specular r g b
	-> make a Color with the r g b
	-> update specular to this Color

diffuse s
	-> update shininess to this value

emission r g b
	-> make a Color with the r g b
	-> update emission to this Color




Need to return:
	The Scene
	The Camera
	The Options
*/