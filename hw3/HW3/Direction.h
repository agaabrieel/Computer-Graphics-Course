#pragma once

// Direction struct, essentially a 3-d unit vector, but there is already a cpp class vector, so using the name Direction to avoid name clashes
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
		~Direction();

		float x() const;
		float y() const;
		float z() const;

	private:
		float _x;
		float _y;
		float _z;

		void normalise();
};

