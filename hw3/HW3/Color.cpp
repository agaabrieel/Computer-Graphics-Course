#include "Color.h"
#include <math.h>

Color::Color() : Color(0.0, 0.0, 0.0) {}

Color::Color(float red, float green, float blue) : _red(red), _green(green), _blue(blue) {}

Color::Color(glm::vec3 rgb) : Color(rgb.r, rgb.g, rgb.b)
{
}

float Color::red() const { return _red; }
float Color::green() const { return _green; }
float Color::blue() const { return _blue; }

glm::vec3 Color::toGlmVec3()
{
	return glm::vec3(_red, _green, _blue);
}

RGBTRIPLE Color::to_freeimage_rgbtriple() const
{
	RGBTRIPLE triple;
	triple.rgbtBlue = color_channel_float_to_byte(_blue);
	triple.rgbtGreen = color_channel_float_to_byte(_green);
	triple.rgbtRed = color_channel_float_to_byte(_red);
	return triple;
}

Color Color::operator+(const Color& c) const
{
	return Color(this->_red + c._red, this->_green + c._green, this->_blue + c._blue);
}

Color Color::operator*(const Color& c) const
{
	return Color(
		_red * c._red,
		_green * c._green,
		_blue * c._blue
	);
}

Color Color::operator*(float f) const
{
	return Color(
		_red * f,
		_green * f,
		_blue * f
	);
}

void Color::operator=(const Color& c)
{
	_red = c._red;
	_green = c._green;
	_blue = c._blue;
}

void Color::operator+=(const Color& c)
{
	_red += c._red;
	_green += c._green;
	_blue += c._blue;
}

void Color::operator/=(float f)
{
	_red /= f;
	_green /= f;
	_blue /= f;
}

BYTE Color::color_channel_float_to_byte(float color_channel) const
{
	return (BYTE)floor(color_channel >= 1.0 ? 255 : color_channel * 256.0);
}
