// Contains class to contain scene description

/*
A scene has:

size: width and height
objects (shapes): spheres and triangles
lights: directional, point (+global ambient default (.2, .2, .2) [allow to specify in constructor] - this can be overridden by object's ambient term ?)

A Scene can:

addShape(Shape)
addLight(Light)
*/