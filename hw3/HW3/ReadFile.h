#pragma once
#include <sstream>

namespace ReadFile {

	// From HW2
	bool readvals(std::stringstream& s, const int numvals, float* values); // Does this need to be GLfloat? Maybe it's a float[] ?
	void readfile(const char* filename);

}
