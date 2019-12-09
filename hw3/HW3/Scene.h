#pragma once
#include <vector>
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Camera.h"
#include "Intersection.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include <optional>


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

// TODO: put in name space
struct IntersectionAsStruct {
	Shape* intersected_shape;
	Point intersection_location;
};

class Scene
{
	public:
		Scene(int width, int height, Camera camera);
		Scene(int width, int height, Camera camera, Color ambient_global);
		~Scene();

		//void addShape(Shape* shape);  // We can store all Shapes together in the same list because we only need to call the method intersect(Ray)
		//								// on them, which all Shape subclasses must implement separately
		void addTriangle(Triangle triangle); // Possibly add an option to add a vector of shapes.
		void addSphere(Sphere sphere);
		void addDirectionalLight(DirectionalLight directional_light);  // We must store separate lists of Light subclasses because we need to access
		void addPointLight(PointLight point_light);						// different information from them - i.e. we need to know that a PointLight is
																		// a PointLight, and not a DirectionalLight.

		int width() const;
		int height() const;

		Ray rayThroughPixel(int i, int j) const; // Returns the ray that goes from the camera through the "viewing screen" at pixel with coords i, j
		 
		void intersect(const Ray& ray, std::optional<IntersectionAsStruct>& intersection) const;  // finds the object in the scene that is closest to the camera and intersects the ray
	
		Color findColor(IntersectionAsStruct intersection, int recursive_depth_permitted) const; // Finds the appropriate color given the object and location in intersection

		BYTE* raytrace(int max_recursion_depth) const; // Returns a byte array containing the pixels of the raytraced image
			// Possibility: have the option maxdepth passed here
						// don't pass the output file name to the scene, we can just pass back the byte array from here, and then main can write the file out.

	private:
		const Camera _camera;
		const int _width;
		const int _height;
		float _aspect_ratio;
		float _width_over_two;
		float _height_over_two;
		float _tan_fovx_over_two;
		float _tan_fovy_over_two;
		std::vector<Triangle> _triangles;
		std::vector<Sphere> _spheres;
		std::vector<DirectionalLight> _directional_lights;
		std::vector<PointLight> _point_lights;
		const Color _ambient_global;
};

