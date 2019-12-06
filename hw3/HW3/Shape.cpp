// Contains the class Shape, which will be subclassed by Sphere and Triangle

/* A shape has:

material properties:

diffuse (r, g, b)
specular (r, g, b)
shininess s
emission (r, g, b)

ambient (r, g, b) (possibly null, overrides the scene ambient lighting)

transform -> a matrix describing the transforms applied to it

*/

/*
A sphere has:

center (x, y, z)
radius

*/

/*
A triangle has:

vertexA
vertexB
vertexC

vertices are in counterclockwise order

a vertex is (x, y, z)

*/