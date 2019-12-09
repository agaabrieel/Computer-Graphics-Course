#include "ReadFile.h"
#include <iostream>
#include <fstream>
#include "TransformStack.h"
#include <vector>
#include "Vertex.h"
#include "Triangle.h"
#include "Sphere.h"

#ifndef DEFAULT_FILE_NAME
#define DEFAULT_FILE_NAME "raytrace.png"
#endif

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

ReadFile::FileData ReadFile::readfile(const char* filename)
{
	/*
	need to have:
		list of vertexes (temporary, 0-indexed)
		Scene object
		Options struct
		Camera struct
		*/

	int width = 0, height = 0; // Initialised to 0 so we can check if they aren't defined in the test file.
	int maxdepth = 5; // Default recursive depth of 5.
	unique_ptr<Camera> camera;  // Solution to avoid this is to have a default camera
				// at (0, 0, 0) looking down the -Z axis with up as (0, 1, 0);

	vector<Vertex> vertexes; // Potentially slow since we need to access by random indexes.
								// but we want to allow an arbitrary number of vertexes.
							// However, the bottleneck will probably be in the Raytracing, not Parsing
								// in this program, so I don't think it's a big deal.
	vector<Triangle> triangles;
	vector<Sphere> spheres;
	vector<DirectionalLight> directional_lights;
	vector<PointLight> point_lights;

	// Material properties. Start with additive identity, since Colors are additive.
		// These have to be pointers since they will be reassigned
	unique_ptr<Color> diffuse(new Color(0.0f, 0.0f, 0.0f)); // The scene files allow creating objects without specifying material properties, so I start with black here.
	unique_ptr<Color> specular(new Color(0.0f, 0.0f, 0.0f));
	float shininess = 0;
	unique_ptr<Color> emission(new Color(0.0f, 0.0f, 0.0f)); // Objects do not emit light by default
	unique_ptr<Color> ambient(new Color(0.2f, 0.2f, 0.2f));  // Default value for ambient property of objects
	unique_ptr<Attenuation> attenuation(new Attenuation(1, 0, 0)); // Default attenuation

	// Start a new matrix transform stack with the identity matrix
	TransformStack transform_stack = TransformStack();

	string str, cmd, output_file_name;
	ifstream in;
	in.open(filename);
	if (in.is_open()) {



		getline(in, str);
		while (in) {
			if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
				// Ruled out comment and blank lines 

				stringstream s(str);
				s >> cmd;
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

				else if (cmd == "maxdepth") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						maxdepth = (int)values[0];
					}
				}

				else if (cmd == "output") {
					s >> output_file_name;
				}

				else if (cmd == "camera") {
					validinput = readvals(s, 10, values);
					if (validinput && camera.get() == NULL) { // TODO Only update camera if it has not already been setup. Could throw an error if it is redefined? 
						Point lookfrom = Point(values[0], values[1], values[2]);
						Point lookat = Point(values[3], values[4], values[5]);
						Direction up = Direction(values[6], values[7], values[8]);
						float fovy_degrees = values[9];
						float fovy_radians = glm::radians(fovy_degrees);

						camera.reset(new Camera(lookfrom, lookat, up, fovy_radians));
					}
				}

				else if (cmd == "sphere") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						Point center = Point(values[0], values[1], values[2]);
						float radius = values[3];
						Sphere sphere = Sphere(*diffuse, *specular, shininess, *emission, *ambient,
							transform_stack.top(), center, radius);
						spheres.push_back(sphere);
					}
				}

				else if (cmd == "maxverts") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						// Support for maxverts is optional
						// I ignore it and allow support for an arbitrary number of vertices.
						cout << "Ignoring command maxverts with argument " << values[0] << "\n";
					}
				}

				else if (cmd == "maxvertnorms") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						// Support for maxvertnorms is optional
						cout << "Ignoring command maxvertnorms with argument " << values[0] << "\n";
					}
				}

				else if (cmd == "vertex") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						Vertex vertex = Vertex(values[0], values[1], values[2]);
						vertexes.push_back(vertex);
					}
				}

				else if (cmd == "vertexnormal") {
					validinput = readvals(s, 6, values);
					if (validinput) {
						// Support for vertexnormal is optional
						cout << "Ignoring command vertexnormal with arguments "
							<< values[0] << " "
							<< values[1] << " "
							<< values[2] << " "
							<< values[3] << " "
							<< values[4] << " "
							<< values[5] << "\n";
					}
				}

				else if (cmd == "tri") {
					validinput = readvals(s, 3, values);
					if (validinput && diffuse.get()) {
						Triangle triangle = Triangle(*diffuse, *specular, shininess, *emission, *ambient, transform_stack.top(),
							vertexes.at((int)values[0]),
							vertexes.at((int)values[1]),
							vertexes.at((int)values[2])); // TODO handle outofbounds

						triangles.push_back(triangle);
					}
				}

				else if (cmd == "trinormal") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						// Support for trinormal is optional
						cout << "Ignoring command trinormal with arguments "
							<< values[0] << " "
							<< values[1] << " "
							<< values[2] << "\n";
					}
				}

				else if (cmd == "translate") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						transform_stack.translate(values[0], values[1], values[2]);
					}
				}

				else if (cmd == "rotate") {
					validinput = readvals(s, 4, values);
					if (validinput) {
						float angle_radians = glm::radians(values[3]);
						Direction axis = Direction(values[0], values[1], values[2]);
						transform_stack.rotate(angle_radians, axis);
					}
				}

				else if (cmd == "scale") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						transform_stack.scale(values[0], values[1], values[2]);
					}
				}

				else if (cmd == "pushTransform") {
					transform_stack.pushTransform();
				}

				else if (cmd == "popTransform") {
					transform_stack.popTransform();
				}

				else if (cmd == "directional") {
					validinput = readvals(s, 6, values);
					if (validinput) {
						Direction direction = Direction(values[0], values[1], values[2]);
						Color color = Color(values[3], values[4], values[5]);
						DirectionalLight directional_light = DirectionalLight(color, *attenuation, direction);
						directional_lights.push_back(directional_light);
					}
				}

				else if (cmd == "point") {
					validinput = readvals(s, 6, values);
					if (validinput) {
						Point point = Point(values[0], values[1], values[2]);
						Color color = Color(values[3], values[4], values[5]);
						PointLight point_light = PointLight(color, *attenuation, point);
						point_lights.push_back(point_light);
					}
				}

				else if (cmd == "attenuation") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						attenuation.reset(new Attenuation(values[0], values[1], values[2]));
					}
				}

				else if (cmd == "ambient") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						ambient.reset(new Color(values[0], values[1], values[2]));
					}
				}

				else if (cmd == "diffuse") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						diffuse.reset(new Color(values[0], values[1], values[2]));
					}
				}

				else if (cmd == "specular") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						specular.reset(new Color(values[0], values[1], values[2]));
					}
				}

				else if (cmd == "shininess") {
					validinput = readvals(s, 1, values);
					if (validinput) {
						shininess = values[0];
					}
				}

				else if (cmd == "emission") {
					validinput = readvals(s, 3, values);
					if (validinput) {
						emission.reset(new Color(values[0], values[1], values[2]));
					}
				}

				else {
					cerr << "Unknown Command: " << cmd << " Skipping \n";
				}
			}
			getline(in, str);
		}

		if (width == 0) {
			cerr << "Width was not specified.\n";
			throw 2;
		}

		if (height == 0) {
			cerr << "Height was not specified.\n";
			throw 2;
		}

		if (camera.get() == NULL) {
			cerr << "Camera was not specified.\n";
			throw 2;
		}

		if (output_file_name.size() == 0) {
			output_file_name = DEFAULT_FILE_NAME;
		}

		Scene scene = Scene(width, height, *camera); // Alternative would be to pre-init the scene and add shapes as we go but that is difficult
																// because we wouldn't have the camera. We could make it so the scene isn't initialised
																// with the camera, instead using setCamera, but then we have the situation where the scene
																// may not have a camera, which is also not useful.

		for (Triangle triangle : triangles) {
			scene.addTriangle(triangle);
		}
		for (Sphere sphere : spheres) {
			scene.addSphere(sphere);
		}
		for (DirectionalLight directional_light : directional_lights) {
			scene.addDirectionalLight(directional_light);
		}
		for (PointLight point_light : point_lights) {
			scene.addPointLight(point_light);
		}

		FileData returnData = { scene, output_file_name, maxdepth };
		return returnData;
	}

	else {
		cerr << "Unable to Open Input Data File " << filename << "\n";
		throw 2;
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