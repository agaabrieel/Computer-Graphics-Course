#pragma once

#include <FreeImage.h>
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/glm.hpp>

// Struct for an RGB color
// We can bring all these small files together into a header file such as utilities but for now I'll keep them separate


/* A color has:
r
g
b
*/

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

	private:
		const float _red;
		const float _green;
		const float _blue;

		BYTE color_channel_float_to_byte(float color_channel) const;
};

