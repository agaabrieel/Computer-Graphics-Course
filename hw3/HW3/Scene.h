/* Scene Class:
	
	Contains all information about the Scene, including Lights, Camera, Objects, etc and is able to output a raytraced image based on this information.
*/
#pragma once
#include <vector>
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include <optional>

struct Camera {
	Point lookfrom;
	Point lookat;
	Vector3 up;
	float fovy_radians;
};

// Stores data related to an intersection between a Ray and a Shape
struct Intersection {
	const Shape* intersected_shape;
	Point intersection_location;
	Vector3 normal;
	const Ray& ray;
	float distance;
};

class Scene
{
	public:
		

		

		Scene(int width, int height, Camera camera, std::vector<Triangle> triangles, std::vector<Sphere> spheres, 
			std::vector<DirectionalLight> directional_lights, std::vector<PointLight> point_lights);
	
		int width() const;
		int height() const;

		// Finds the object in the scene that is closest to the camera that intersects the ray, if such an object exists.
		std::optional<Intersection> intersect(const Ray& ray) const;

		// Returns a byte array containing the raw pixels of the raytraced image
		BYTE* raytrace(int max_recursion_depth) const; 
	
	private:
		// Returns the Ray that goes from the camera through the "viewing screen" at pixel with coords i, j
		Ray rayThroughPixel(int i, int j) const;

		// Finds the appropriate color given the object and location in intersection (i.e. it shades the pixel)
		Color findColor(Intersection intersection, int recursive_depth_permitted) const;

		// Scene settings
		const Camera _camera;
		const int _width;
		const int _height;
		const Color _ambient_global;

		// Scene objects
		std::vector<Triangle> _triangles;
		std::vector<Sphere> _spheres;

		// Scene lights
		std::vector<DirectionalLight> _directional_lights;
		std::vector<PointLight> _point_lights;

		// Useful pre-computed values for intersection computation
		float _aspect_ratio;
		float _width_over_two;
		float _height_over_two;
		float _alpha_multiplicand;
		float _beta_multiplicand;
		Vector3 _u;
		Vector3 _v;
		Vector3 _w;
};

