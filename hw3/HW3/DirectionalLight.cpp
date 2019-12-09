#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Color color, Attenuation attenuation, Direction direction) : 
	Light(color, attenuation), _direction(direction) {}

DirectionalLight::~DirectionalLight()
{
}

Direction DirectionalLight::direction() const {	return _direction; }

bool DirectionalLight::isVisibleFrom(Point point) const 
{
	return false;
}
