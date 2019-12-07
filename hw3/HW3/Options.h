#pragma once

// Stores configuration options for the raytracing

/*
maxdepth
output file name
*/

// TODO consider deletion of this class in favour of a struct in the ReadFile namespace that houses the information.

class Options
{
	public:
		Options(int maxdepth, const char* out_file_name);
		~Options();

		int maxdepth() const;
		const char* out_file_name() const;

	private:
		const int _maxdepth;
		const char* _out_file_name;

};

