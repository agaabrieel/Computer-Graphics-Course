#include "Scene.h"
#include "Sphere.h" // TODO remove after implementing intersect


Scene::Scene(int width, int height, Camera camera, Options options) :
	Scene(width, height, camera, options, Color(0.2f, 0.2f, 0.2f)) {}

Scene::Scene(int width, int height, Camera camera, Options options, Color ambient_global) :
	_width(width), _height(height), _camera(camera), _options(options), _ambient_global(ambient_global)
{
	_shapes = std::vector<Shape>();
	_lights = std::vector<Light>();
}

Scene::~Scene()
{
}

void Scene::addShape(Shape shape)
{
	_shapes.push_back(shape);
}

void Scene::addLight(Light light)
{
	_lights.push_back(light);
}

Intersection Scene::intersect(const Ray& ray) const
{
	// Placeholder intersection
	Intersection i = Intersection(Sphere(Color(0, 0, 0), Color(0, 0, 0), 0.0, Color(0, 0, 0), Color(0, 0, 0), glm::mat4(), Point(0, 0, 0), 0.0), Point(0, 0, 0));
	return i; //TODO
}
