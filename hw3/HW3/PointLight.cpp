#include "PointLight.h"

PointLight::PointLight(Color color, Attenuation attenuation, Point point) : Light(color, attenuation), _point(point) {}

PointLight::~PointLight()
{
}

Point PointLight::point() const { return _point; }
