#include "Camera.h"

Camera::Camera(Point lookfrom, Point lookat, Vector3 up, float fovy_radians) :
	_lookfrom(lookfrom), _lookat(lookat), _up(up.normalize()), _fovy_radians(fovy_radians) {}

Point Camera::lookfrom() const { return _lookfrom; }

Point Camera::lookat() const { return _lookat; }

Vector3 Camera::up() const { return _up; }

float Camera::fovy_radians() const { return _fovy_radians; }
