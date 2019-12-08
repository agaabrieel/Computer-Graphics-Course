#include "Color.h"

Color::Color() : Color(0.0, 0.0, 0.0) {}

Color::Color(float red, float green, float blue) : _red(red), _green(green), _blue(blue) {}

Color::~Color()
{
}

float Color::red() const { return _red; }

float Color::green() const { return _green; }

float Color::blue() const { return _blue; }

BYTE Color::color_as_byte() const
{
	return 0; // TODO
}
