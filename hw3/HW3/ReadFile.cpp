#include "ReadFile.h"
#include <iostream>
#include <fstream>
#include "TransformStack.h"
#include <vector>
#include "Vertex.h"
#include "Scene.h"
#include "Triangle.h"
#include "Sphere.h"

using namespace std;

// Function to read the input data values
// From HW2 skeleton.
bool ReadFile::readvals(std::stringstream& s, const int numvals, float* values)
{
	for (int i = 0; i < numvals; i++) {
		s >> values[i];
		if (s.fail()) {
			cout << "Failed reading value " << i << " will skip\n";
			return false;
		}
	}
	return true;
}

void ReadFile::readfile(const char* filename)
{
	/*
	need to have:
		list of vertexes (temporary, 0-indexed)
		Scene object
		Options struct
		Camera struct
		*/

	int width, height, maxdepth;
	Camera* camera;

	vector<Vertex> vertexes; // Potentially slow since we need to access by random indexes.
								// but we want to allow an arbitrary number of vertexes.
							// However, the bottleneck will probably be in the Raytracing, not Parsing
								// in this program, so I don't think it's a big deal.
	vector<Triangle> triangles;
	vector<Sphere> spheres;
	vector<DirectionalLight> directionalLights;
	vector<PointLight> pointLights;

	// Material properties. Start with additive identity, since Colors are additive.
	Color diffuse;
	Color specular;
	float shininess = 0;
	Color emission;
	Color ambient = Color(0.2, 0.2, 0.2);  // Default for ambient

	// Start a new matrix transform stack with the identity matrix
	TransformStack transformStack = TransformStack();
	
	string str, cmd, output_file_name;
	ifstream in;
	in.open(filename);
	if (in.is_open()) {

		

		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				// Ruled out comment and blank lines 
			}

			stringstream s(str);
			s >> cmd;
			int i;
			float values[10]; // Stores the parameters for the command. Need up to 10 for camera.
								// Using float instead of GLfloat to see if we can remove dependency on OpenGL.
			bool validinput;

			if (cmd == "size") {
				validinput = readvals(s, 2, values);
				if (validinput) {
					width = (int)values[0];
					height = (int)values[1];
				}
			}

			if (cmd == "maxdepth") {
				validinput = readvals(s, 1, values);
				if (validinput) {
					maxdepth = (int)values[0];
				}
			}

			if (cmd == "output") {
				s >> output_file_name;
			}

			if (cmd == "camera") {
				validinput = readvals(s, 10, values);
				if (validinput) {
					Point lookfrom = Point(values[0], values[1], values[2]);
					Point lookat = Point(values[3], values[4], values[5]);
					Direction up = Direction(values[6], values[7], values[8]);
					float fovy_degrees = values[9];
					float fovy_radians = glm::radians(fovy_degrees);

					Camera camera = Camera(lookfrom, lookat, up, fovy_radians);
					// TODO how to get this into higher scope?
						// Could use pointer but then we have to make sure to free it.
				}
			}

			if (cmd == "sphere") {
				validinput = readvals(s, 4, values);
				if (validinput) {
					Point center = Point(values[0], values[1], values[2]);
					float radius = values[3];
					Sphere sphere = Sphere(diffuse, specular, shininess, emission, ambient,
						transformStack.top(), center, radius);
					spheres.push_back(sphere);
				}
			}

			if (cmd == "maxverts") {
				validinput = readvals(s, 1, values);
				if (validinput) {
					// Support for maxverts is optional
					// I ignore it and allow support for an arbitrary number of vertices.
					cout << "Ignoring command maxverts with argument " << values[0];
				}
			}

			if (cmd == "maxvertnorms") {
				validinput = readvals(s, 1, values);
				if (validinput) {
					// Support for maxvertnorms is optional
					// I ignore it and allow support for an arbitrary number of vertices.
					cout << "Ignoring command maxvertnorms with argument " << values[0];
				}
			}

			if (cmd == "vertex") {
				validinput = readvals(s, 3, values);
				if (validinput) {
					Vertex vertex = Vertex(values[0], values[1], values[2]);
					vertexes.push_back(vertex);
				}
			}


		}


	}
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