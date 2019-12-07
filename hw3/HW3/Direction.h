#pragma once

// Direction struct, essentially a 3-d vector, but there is already a cpp class vector, so using the name Direction to avoid name clashes
// We can bring all these small files together into a header file such as utilities but for now I'll keep them separate

/*
A direction has:

x
y
z


Invariant: Stored in normalised form
*/


class Direction
{
	public:
		Direction(float x, float y, float z);

		float x() const;
		float y() const;
		float z() const;

	private:
		const float _x;
		const float _y;
		const float _z;
};

