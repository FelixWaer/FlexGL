#pragma once
#include <vector>

struct Vertex;
struct Triangle;

class Mesh
{
public:
	std::vector<Vertex> Vertices;
	std::vector<Triangle> Triangles;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	uint64_t TotalDraws = 0;

	void bind_Buffer(int drawType);
	void rebind_Buffer(int drawType);
	void delete_Buffer();
};

