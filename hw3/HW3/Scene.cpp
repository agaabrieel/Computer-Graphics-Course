#include "Scene.h"
#include "Sphere.h" // TODO remove after implementing intersect
#include "Triangle.h"


Scene::Scene(int width, int height, Camera camera) :
	Scene(width, height, camera, Color(0.2f, 0.2f, 0.2f)) {}

Scene::Scene(int width, int height, Camera camera, Color ambient_global) :
	_width(width), _height(height), _camera(camera), _ambient_global(ambient_global)
{
	_triangles = std::vector<Triangle>();
	_spheres = std::vector<Sphere>();
	_point_lights = std::vector<PointLight>();
	_directional_lights = std::vector<DirectionalLight>();
}

Scene::~Scene()
{
	// Need to delete the Shapes and Lights?
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
	return Ray(Point(0, 0, 0), Direction(0, 0, 0)); // TODO
}

Intersection Scene::intersect(const Ray& ray) const
{
	// Placeholder intersection
	Intersection i = Intersection(new Sphere(Color(0, 0, 0), Color(0, 0, 0), 0.0, Color(0, 0, 0), Color(0, 0, 0), glm::mat4(), Point(0, 0, 0), 0.0), Point(0, 0, 0));
	return i; //TODO
}

Color Scene::findColor(Intersection intersection) const
{
	return Color(0, 0, 0); // TODO
}

BYTE* Scene::raytrace(int max_recursion_depth) const
{
	return nullptr; // TODO
}
