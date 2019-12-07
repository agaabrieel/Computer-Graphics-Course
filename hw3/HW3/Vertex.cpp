#include "Vertex.h"

Vertex::Vertex(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vertex::~Vertex()
{
}

float Vertex::x() const { return _x; }

float Vertex::y() const { return _y; }

float Vertex::z() const { return _z; }
