#pragma once
class Vector
{
	public:
		Vector(float x, float y, float z);
		~Vector();

		float x() const;
		float y() const;
		float z() const;

	protected:
		float _x;
		float _y;
		float _z;
};

