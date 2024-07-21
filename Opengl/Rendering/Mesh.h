#pragma once
#include <string>
#include <vector>

#include "MeshData.h"

class Mesh
{
public:
	void load_MeshObj(const std::string& filePath);
	void load_MeshTxt(const std::string& filePath);
	void create_CubeMesh();
	void bind_Buffer(int drawType);
	void rebind_Buffer(int drawType);
	void delete_Buffer();

	void bind_VAOBuffer();

	std::vector<Vertex> Vertices;
	std::vector<Triangle> Triangles;
private:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	uint64_t TotalDraws = 0;
};

