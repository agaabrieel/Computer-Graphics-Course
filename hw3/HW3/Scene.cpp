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

Intersection Scene::intersect(const Ray& ray) const
{
	// Placeholder intersection
	Intersection i = Intersection(new Sphere(Color(0, 0, 0), Color(0, 0, 0), 0.0, Color(0, 0, 0), Color(0, 0, 0), glm::mat4(), Point(0, 0, 0), 0.0), Point(0, 0, 0));
	return i; //TODO implement Scene::intersect
}

Color Scene::findColor(Intersection intersection) const
{
	// TODO: for now, using glm::vec3 to handle the vector operations. Later on, could add operations to the custom Vector class.

	Shape* intersected_shape = intersection.shape();

	// Ambient term, per object
	glm::vec3 final_color = intersected_shape->ambient().toGlmVec3();

	// Emission term, per object
	final_color += intersected_shape->emission().toGlmVec3();

	for (PointLight point_light : _point_lights) {
		// TODO: implement point_light contribution to color
	}

	for (DirectionalLight directional_light : _directional_lights) {
		// TODO: implement directional_light contribution to color
	}

	// TODO: implement recursive element

	return Color(final_color.x, final_color.y, final_color.z);
}

BYTE* Scene::raytrace(int max_recursion_depth) const
{
	return nullptr; // TODO implement Scene::raytrace
}
