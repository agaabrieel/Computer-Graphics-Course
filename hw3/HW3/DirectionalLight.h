#pragma once
#include "Light.h"


/*
A DirectionalLight also has:

direction (x, y, z)

*/

class DirectionalLight :
	public Light
{

	private:
		Direction direction;
};

