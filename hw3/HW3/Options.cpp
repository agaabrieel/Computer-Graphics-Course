#include "Options.h"

Options::Options(int maxdepth, const char* out_file_name) : _maxdepth(maxdepth), _out_file_name(out_file_name) {}

Options::~Options()
{
}

int Options::maxdepth() const { return _maxdepth; }

const char* Options::out_file_name() const { return _out_file_name; }
