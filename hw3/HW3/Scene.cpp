#include "Scene.h"
#include "Sphere.h" // TODO remove after implementing intersect
#include "Triangle.h"
#include <memory>


Scene::Scene(int width, int height, Camera camera) :
	Scene(width, height, camera, Color(0.2f, 0.2f, 0.2f)) {}

Scene::Scene(int width, int height, Camera camera, Color ambient_global) :
	_width(width), _height(height), _camera(camera), _ambient_global(ambient_global)
{
	_triangles = std::vector<Triangle>();
	_spheres = std::vector<Sphere>();
	_point_lights = std::vector<PointLight>();
	_directional_lights = std::vector<DirectionalLight>();

	// Precompute these values now since they will be needed repeatedly and won't change.
	_aspect_ratio = (float)_width / (float)_height;
	_width_over_two = _width / 2.0f;
	_height_over_two = _height / 2.0f;
	_tan_fovy_over_two = tan(_camera.fovy_radians() / 2);
	_tan_fovx_over_two = _tan_fovy_over_two * _aspect_ratio;
}

Scene::~Scene()
{
}

void Scene::addTriangle(Triangle triangle)
{
	_triangles.push_back(triangle);
}

void Scene::addSphere(Sphere sphere)
{
	_spheres.push_back(sphere);
}

void Scene::addDirectionalLight(DirectionalLight directional_light)
{
	_directional_lights.push_back(directional_light);
}

void Scene::addPointLight(PointLight point_light)
{
	_point_lights.push_back(point_light);
}



int Scene::width() const { return _width; }

int Scene::height() const {	return _height; }

Ray Scene::rayThroughPixel(int i, int j) const
{
	glm::vec3 center = _camera.lookat().toGlmVec3(); // center is what we are looking at
	glm::vec3 eye = _camera.lookfrom().toGlmVec3(); // eye is the camera location
	glm::vec3 a = eye - center;

	glm::vec3 b = _camera.up().toGlmVec3();

	glm::vec3 w = glm::normalize(a);
	
	glm::vec3 u = glm::cross(b, w);
	u = glm::normalize(u);

	glm::vec3 v = glm::cross(w, u);

	float alpha = _tan_fovx_over_two * ((j - _width_over_two) / _width_over_two);
	float beta = _tan_fovy_over_two * ((_height_over_two - i) / _height_over_two);

	glm::vec3 direction = alpha * u + beta * v - w;
	direction = glm::normalize(direction);

	// The ray has origin at the camera location and looks in the given direction
	return Ray(_camera.lookfrom(), Direction(direction.x, direction.y, direction.z)); 
}

std::optional<Intersection> Scene::intersect(const Ray& ray) const
{
	float mindist = INFINITY;
	Shape* hit_object = NULL;

	// Ideally these two loops would be merged but I found it problematic storing shapes:
		// Shape class is abstract and C++ requires pointers to store derived objects.
	for (Triangle triangle : _triangles) {
		std::optional<float> t = triangle.intersect(ray);
		if (t.has_value() && t.value() < mindist) {
			mindist = t.value();
			hit_object = &triangle;
		}
	}

	for (Sphere sphere : _spheres) {
		std::optional<float> t = sphere.intersect(ray);
		if (t.has_value() && t.value() < mindist) {
			mindist = t.value();
			hit_object = &sphere;
		}
	}

	if (hit_object == NULL) {
		return std::nullopt;
	}

	glm::vec3 intersection_location = ray.origin().toGlmVec3() + mindist * ray.direction().toGlmVec3();
	Point p = Point(intersection_location.x, intersection_location.y, intersection_location.z);

	Intersection i = Intersection(hit_object, p);
	return { i };
}

Color Scene::findColor(Intersection intersection, int recursive_depth_permitted) const
{
	// Base case: no more reflections permitted
	if (recursive_depth_permitted < 1) {
		return Color(0.0f, 0.0f, 0.0f);
	}

	// TODO: for now, using glm::vec3 to handle the vector operations. Later on, could add operations to the custom Vector class.

	Shape* intersected_shape = intersection.shape();

	// Ambient term, per object
	glm::vec3 final_color = intersected_shape->ambient().toGlmVec3();

	// Emission term, per object
	final_color += intersected_shape->emission().toGlmVec3();

	for (PointLight point_light : _point_lights) {
		// If the light is visible from the intersection location
			// Compute the diffuse component to the final color
			// Compute the specular component to the final color		

		// Attenuation:
			// Light contribution / (const + lin * dist + quad * dist^2)
		// TODO: implement point_light contribution to color
	}

	for (DirectionalLight directional_light : _directional_lights) {
		// If the light is visible from the intersection location
			// Add the diffuse component to the final color
			// Add the specular component to the final color	

		// No attenuation?
		// TODO: implement directional_light contribution to color
	}

	// TODO: implement recursive element
	// specular * findColor(reflected ray, recursive_depth_permitted - 1)

	return Color(final_color.x, final_color.y, final_color.z);
}

// TODO return smart pointer
BYTE* Scene::raytrace(int max_recursion_depth) const
{
	int pix = _width * _height;
	BYTE* pixels = new BYTE[3 * pix];

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			Ray ray = rayThroughPixel(i, j);
			std::optional<Intersection> intersection = intersect(ray);
			if (intersection.has_value()) {
				//Color pixel_color = findColor(intersection.value(), max_recursion_depth);
				Color pixel_color = Color(0.0f, 0.0f, 1.0f); // TODO: debug value: objects in view are coloured pure blue
				RGBTRIPLE pixel_color_triple = pixel_color.to_freeimage_rgbtriple();
				int pixel_start_index = (i * _width * 3) + (j * 3);

				// BlueGreenRed. TODO: consider copying memory as 3 bytes together
				pixels[pixel_start_index] = pixel_color_triple.rgbtBlue;   // TODO check indexes
				pixels[pixel_start_index + 1] = pixel_color_triple.rgbtGreen;
				pixels[pixel_start_index + 2] = pixel_color_triple.rgbtRed;
			}
			else { // No intersection so use global ambient value.
				//Color pixel_color = _ambient_global;
				Color pixel_color = Color(1.0f, 0.0f, 0.0f); // TODO: debug value: background is pure red.
				RGBTRIPLE pixel_color_triple = pixel_color.to_freeimage_rgbtriple();
				int pixel_start_index = (i * _width * 3) + (j * 3);

				// BlueGreenRed. TODO: consider copying memory as 3 bytes together
				pixels[pixel_start_index] = pixel_color_triple.rgbtBlue;   // TODO check indexes
				pixels[pixel_start_index + 1] = pixel_color_triple.rgbtGreen;
				pixels[pixel_start_index + 2] = pixel_color_triple.rgbtRed;

				// TODO reduce duplication : smart pointer to pixel_color
			}
		}
	}

	return pixels;
}
