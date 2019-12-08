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
	unique_ptr<FIBITMAP> img( // Using a smart pointer to avoid having to delete the pixel array.
		FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false));
	std::cout << "Saving screenshot: " << fname << "\n";
	FreeImage_Save(FIF_PNG, img.get(), fname.c_str(), 0);
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Usage: Raytracer.exe scenefile\n";
		exit(-1);
	}

	FreeImage_Initialise();

	ReadFile::FileData sceneData = ReadFile::readfile(argv[1]);
	Scene scene = sceneData.scene;
	
	BYTE* pixels = scene.raytrace(sceneData.max_recursion_depth);
	saveImage(scene.width(), scene.height(), pixels, sceneData.output_filename);

	FreeImage_DeInitialise();
	return 0;
}
