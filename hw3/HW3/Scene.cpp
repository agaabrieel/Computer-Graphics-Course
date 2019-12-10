#include "Scene.h"
#include "Sphere.h" // TODO remove after implementing intersect
#include "Triangle.h"
#include <memory>
#include "ProgressBar.hpp"  // https://github.com/prakhar1989/progress-cpp

Scene::Scene(int width, int height, Camera camera) :
	// Default value for the background in the reference images appears to be pitch black, not (0.2, 0.2, 0.2)
	Scene(width, height, camera, Color(0.0f, 0.0f, 0.0f)) {}

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
	// TODO ray should go through center of pixel!

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



void Scene::intersect(const Ray& ray, std::optional<IntersectionAsStruct>& intersection) const
{
	float mindist = INFINITY;
	std::optional<Shape*> hit_object;
	glm::vec3 normal;

	// Ideally these two loops would be merged but I found it problematic storing shapes:
		// Shape class is abstract and C++ requires pointers to store derived objects.
	for (Triangle triangle : _triangles) {
		std::optional<DistanceAndNormal> result = triangle.intersect(ray);
		if (result.has_value() && result.value().distance < mindist) {
			mindist = result.value().distance;
			// TODO: a bad hack. This works but now we're creating new objects in each loop.
				// Is there a way to get a meaningful pointer to the object in the Scene and return that pointer
				// such that the pointer does not end up pointing to garbage?
			hit_object.reset(); 
			hit_object = new Triangle(triangle);
			normal = result.value().normal;
		}
	}

	for (Sphere sphere : _spheres) {
		std::optional<DistanceAndNormal> result = sphere.intersect(ray);
		if (result.has_value() && result.value().distance < mindist) {
			mindist = result.value().distance;
			hit_object.reset();
			hit_object = new Sphere(sphere);
			normal = result.value().normal;
		}
	}

	if (!hit_object.has_value()) {
		return;
	}

	glm::vec3 intersection_location = ray.origin().toGlmVec3() + mindist * ray.direction().toGlmVec3();
	Point p = Point(intersection_location);

	IntersectionAsStruct i = { hit_object.value(), p, normal, ray };
	intersection.emplace(i);
	return;
}

Color Scene::findColor(IntersectionAsStruct intersection, int recursive_depth_permitted) const
{
	// Base case: no more reflections permitted
	if (recursive_depth_permitted < 1) {
		return Color(0.0f, 0.0f, 0.0f); // Colors are additive so we can just return black.
	}

	// TODO: for now, using glm::vec3 to handle the vector operations. Later on, could add operations to the custom Vector class.

	Shape* intersected_shape = intersection.intersected_shape;

	// Ambient term, per object
	glm::vec3 final_color = intersected_shape->ambient().toGlmVec3();

	// Emission term, per object
	final_color += intersected_shape->emission().toGlmVec3();

	for (PointLight point_light : _point_lights) {

		bool isVisible = point_light.isVisibleFrom(intersection.intersection_location, this);
		if (isVisible) { 
			// TODO this is duplicated code form isVisibleFrom
			glm::vec3 light_direction = point_light.point().toGlmVec3() - intersection.intersection_location.toGlmVec3();
			light_direction = glm::normalize(light_direction);
			float l_dot_n = glm::dot(light_direction, intersection.normal);

			// diffuse
			final_color += point_light.color().toGlmVec3() * intersected_shape->diffuse().toGlmVec3() * glm::max(l_dot_n, 0.0f);

			// specular
			glm::vec3 half_angle = (-intersection.ray.direction().toGlmVec3()) + light_direction;
			half_angle = glm::normalize(half_angle);
			float h_dot_n = glm::dot(half_angle, intersection.normal);

			final_color += point_light.color().toGlmVec3() * intersected_shape->specular().toGlmVec3() * (pow(glm::max(h_dot_n, 0.0f), intersected_shape->shininess()));
		}


		// TODO: Attenuation:
			// Light contribution / (const + lin * dist + quad * dist^2)
	}

	for (DirectionalLight directional_light : _directional_lights) {
		bool isVisible = directional_light.isVisibleFrom(intersection.intersection_location, this);
		if (isVisible) { 
			// No need to compute the direction
			glm::vec3 light_direction = directional_light.direction().toGlmVec3();
			float l_dot_n = glm::dot(light_direction, intersection.normal);

			// diffuse
			final_color += directional_light.color().toGlmVec3() * intersected_shape->diffuse().toGlmVec3() * glm::max(l_dot_n, 0.0f);

			// specular
			glm::vec3 half_angle = (-intersection.ray.direction().toGlmVec3()) + light_direction;
			half_angle = glm::normalize(half_angle);
			float h_dot_n = glm::dot(half_angle, intersection.normal);

			final_color += directional_light.color().toGlmVec3() * intersected_shape->specular().toGlmVec3() * (pow(glm::max(h_dot_n, 0.0f), intersected_shape->shininess()));
		}
		// No attenuation?
		// TODO: implement directional_light contribution to color
	}

	// It's expensive to compute the reflected ray and intersection, so let's not do it unless we need to.
	// TODO Check that there is a significant specular component to the intersected object.
	if (recursive_depth_permitted > 1) {
		glm::vec3 original_ray_direction = intersection.ray.direction().toGlmVec3();
		glm::vec3 reflected_ray_origin = intersection.intersection_location.toGlmVec3();
		glm::vec3 reflected_ray_direction = original_ray_direction + 2.0f * (glm::dot(-original_ray_direction, intersection.normal)) * intersection.normal;
		reflected_ray_direction = glm::normalize(reflected_ray_direction);
		reflected_ray_origin += 0.0001f * reflected_ray_direction; // TODO check if necessary, pushes reflected ray slightly away from object
		Ray reflected_ray = Ray(Point(reflected_ray_origin), Direction(reflected_ray_direction));
		std::optional<IntersectionAsStruct> reflected_intersection = std::nullopt;
		intersect(reflected_ray, reflected_intersection);

		if (reflected_intersection.has_value()) {

			glm::vec3 recursive_specular_component = intersected_shape->specular().toGlmVec3() * findColor(reflected_intersection.value(), recursive_depth_permitted - 1).toGlmVec3();
			final_color += recursive_specular_component;
		}
	}

	return Color(final_color.x, final_color.y, final_color.z);
}

// TODO return smart pointer
BYTE* Scene::raytrace(int max_recursion_depth) const
{
	int pix = _width * _height;
	BYTE* pixels = new BYTE[3 * pix];
	ProgressBar progressBar(_height, 70);

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			Ray ray = rayThroughPixel(i, j);
			std::optional<IntersectionAsStruct> intersection = std::nullopt;
			intersect(ray, intersection);
			if (intersection.has_value()) {
				Color pixel_color = findColor(intersection.value(), max_recursion_depth);
				//Color pixel_color = Color(0.0f, 0.0f, 1.0f); // TODO: debug value: objects in view are coloured pure blue
				RGBTRIPLE pixel_color_triple = pixel_color.to_freeimage_rgbtriple();
				int pixel_start_index = (i * _width * 3) + (j * 3);

				// BlueGreenRed. TODO: consider copying memory as 3 bytes together
				pixels[pixel_start_index] = pixel_color_triple.rgbtBlue;   // TODO check indexes
				pixels[pixel_start_index + 1] = pixel_color_triple.rgbtGreen;
				pixels[pixel_start_index + 2] = pixel_color_triple.rgbtRed;
			}
			else { // No intersection so use global ambient value.
				Color pixel_color = _ambient_global;
				//Color pixel_color = Color(0.5f, 0.0f, 0.0f); // TODO: debug value: background is pure dark red.
				RGBTRIPLE pixel_color_triple = pixel_color.to_freeimage_rgbtriple();
				int pixel_start_index = (i * _width * 3) + (j * 3);

				// BlueGreenRed. TODO: consider copying memory as 3 bytes together
				pixels[pixel_start_index] = pixel_color_triple.rgbtBlue;   // TODO check indexes
				pixels[pixel_start_index + 1] = pixel_color_triple.rgbtGreen;
				pixels[pixel_start_index + 2] = pixel_color_triple.rgbtRed;

				// TODO reduce duplication : smart pointer to pixel_color
			}
		}
		++progressBar;
		progressBar.display();
	}
	  
	progressBar.done();
	return pixels;
}
