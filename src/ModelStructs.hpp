#pragma once

#include <vector>

struct Vertex
{
	float x, y, z;
	float nx, ny, nz; //Normal of vertex
	float u, v;

	Vertex() { }
	Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) : x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), u(u), v(v) { }
};

struct Triangle
{
	unsigned int a, b, c; //Indices of Vertexes

	Triangle() : a(-1), b(-1), c(-1) { }
	Triangle(unsigned int a, unsigned int b, unsigned int c) : a(a), b(b), c(c) { }
};

struct Model
{
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;
};