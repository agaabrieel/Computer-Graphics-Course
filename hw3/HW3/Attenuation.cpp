#include "Attenuation.h"

Attenuation::Attenuation(float constant, float linear, float quadratic) : _constant(constant), _linear(linear), _quadratic(quadratic) {}

Attenuation::~Attenuation()
{
}

float Attenuation::constant() const { return _constant; }

float Attenuation::linear() const {	return _linear; }

float Attenuation::quadratic() const { return _quadratic; }

std::tuple<float, float, float> Attenuation::values() const
{
	return std::tuple<float, float, float>(_constant, _linear, _quadratic);
}
