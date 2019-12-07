#include "Light.h"

Light::Light(Color color, Attenuation attenuation) : _color(color), _attenuation(attenuation) {}

Light::~Light()
{
}

Color Light::color() const { return _color; }

Attenuation Light::attenuation() const { return _attenuation; }
