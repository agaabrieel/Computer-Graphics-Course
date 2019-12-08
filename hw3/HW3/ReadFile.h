#pragma once
#include <sstream>
#include <string>

#include "Scene.h"

namespace ReadFile {

	struct FileData {
		Scene scene;
		std::string output_filename;
		int max_recursion_depth;
	};

	// From HW2
	bool readvals(std::stringstream& s, const int numvals, float* values); // Does this need to be GLfloat? Maybe it's a float[] ?
	FileData readfile(const char* filename);

}
