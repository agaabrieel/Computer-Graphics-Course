#pragma once
#include <FreeImage.h>
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>

class Color
{
	public:
		Color(); // Initialise Color with (0, 0, 0)
		Color(float red, float green, float blue);
		Color(glm::vec3 rgb);

		float red() const;
		float green() const;
		float blue() const;

		glm::vec3 toGlmVec3();
		RGBTRIPLE to_freeimage_rgbtriple() const;

		Color operator+(const Color& c) const;
		Color operator*(const Color& c) const;
		Color operator*(float f) const;
		void operator=(const Color& c);
		void operator+=(const Color& c);
		void operator/=(float f);

	private:
		float _red;
		float _green;
		float _blue;

		BYTE color_channel_float_to_byte(float color_channel) const;
};

