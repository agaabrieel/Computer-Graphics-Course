// HW3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// This file will execute the raytracer:
	// Read input file
	// Parse to scene, camera descriptions
	// Raytrace
	// Output image file

#include <iostream>
#include <FreeImage.h>
#include "ReadFile.h"

using namespace std;

// Adapted from HW2 skeleton code.
void saveImage(int width, int height, BYTE* pixels, string fname) {
	// TODO: the final argument (true) says to read the BITMAP from top to bottom.
		// We are building the bitmap this way. Check if this is slower than bottom to top.
		// If so, we can build the bitmap the other way.
	FIBITMAP* img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	std::cout << "Saving screenshot: " << fname << "\n";
	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
	// TODO Do i need to free the img data here?
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Usage: Raytracer.exe scenefile\n";
		exit(-1);
	}

	// TODO add pretty status messages

	ReadFile::FileData sceneData = ReadFile::readfile(argv[1]);
	Scene scene = sceneData.scene;
	
	BYTE* pixels = scene.raytrace(sceneData.max_recursion_depth);

	FreeImage_Initialise();
	saveImage(scene.width(), scene.height(), pixels, sceneData.output_filename);
	// TODO do i need to free the pixels here?
	FreeImage_DeInitialise();
	return 0;
}
