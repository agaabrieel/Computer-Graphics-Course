#include "Camera.h"

Camera::Camera(Point lookfrom, Point lookat, Direction up, float fovy_radians) :
	_lookfrom(lookfrom), _lookat(lookat), _up(up), _fovy_radians(fovy_radians) {}

Camera::~Camera()
{
}

Point Camera::lookfrom() const { return _lookfrom; }

Point Camera::lookat() const { return _lookat; }

Direction Camera::up() const { return _up; }

float Camera::fovy_radians() const { return _fovy_radians; }
