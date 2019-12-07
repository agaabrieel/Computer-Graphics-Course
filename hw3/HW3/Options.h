#pragma once

// Stores configuration options for the raytracing

/*
maxdepth
output file name
*/

class Options
{
	public:
		Options(int maxdepth, char out_file_name);

		int maxdepth() const;
		char* out_file_name() const;

	private:
		const int _maxdepth;
		const char* _out_file_name;

};

