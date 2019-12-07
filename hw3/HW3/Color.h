#pragma once

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
		Color(float red, float green, float blue);

		float red() const;
		float green() const;
		float blue() const;

	private:
		const float _red;
		const float _green;
		const float _blue;
};

