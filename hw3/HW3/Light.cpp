#include "Light.h"

Light::Light(Color color) : _color(color) {}

Color Light::color() const { return _color; }

