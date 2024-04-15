#pragma once
#include <vector>

class Vertex;
struct Triangle;

class Mesh
{
public:
	std::vector<Vertex> Vertices;
	std::vector<Triangle> Triangles;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void bind_Buffer();
private:
};

