#pragma once

//Point struct

// We can bring all these small files together into a header file such as utilities but for now I'll keep them separate

/*
A Point has

x
y
z
*/

class Point
{
	public:
		Point(float x, float y, float z);

	private:
		float x;
		float y;
		float z;

};

