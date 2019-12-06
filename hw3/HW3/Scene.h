#pragma once
#include <vector>


// Contains class to contain scene description

/*
A scene has:

size: width and height
objects (shapes): spheres and triangles
lights: directional, point (+global ambient default (.2, .2, .2) [allow to specify in constructor] - this can be overridden by object's ambient term ?)

A Scene can:

addShape(Shape)
addLight(Light)
*/

class Scene
{
	public:
		Scene(int width, int height, Color ambient_global);
		void addShape(Shape shape);
		void addLight(Light light);

	private:
		int width;
		int height;
		std::vector<Shape> shapes;
		std::vector<Light> lights;
		Color ambient_global;
};

