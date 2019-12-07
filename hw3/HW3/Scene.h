#pragma once
#include <vector>
#include "Shape.h"
#include "Light.h"
#include "Camera.h"


// Contains class to contain scene description

/*
A scene has:

size: width and height
objects (shapes): spheres and triangles
lights: directional, point (+global ambient default (.2, .2, .2) [allow to specify in constructor] - this can be overridden by object's ambient term ?)
a camera
(maybe the scene could have a modelview matrix stack? then
	we could add things like transforms, push transforms, pops, etc
	in that stack class, and we could hide away the matrices)


A Scene can:

addShape(Shape)
addLight(Light)
intersect(Ray) // finds the object in the scene that is closest to the camera and intersects the ray
raytrace() // Returns an image of the scene raytraced.
	// for each pixel, traces a ray and determines the object that intersects
	// finds the color using the intersection. 
*/

class Scene
{
	public:
		Scene(int width, int height);
		Scene(int width, int height, Color ambient_global);
		void addShape(Shape shape);
		void addLight(Light light);

	private:
		const Camera camera;
		const int width;
		const int height;
		std::vector<Shape> shapes;
		std::vector<Light> lights;
		const Color ambient_global;
};

