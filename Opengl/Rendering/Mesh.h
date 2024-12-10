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
	void bind_InstancedBuffer(int drawType);
	void rebind_Buffer(int drawType);
	void rebind_InstancedBuffer(int drawType);
	void delete_Buffer();

	void bind_VAOBuffer();

	std::vector<Vertex> Vertices;
	std::vector<Triangle> Triangles;
	std::vector<glm::mat4> Matrices;
private:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	unsigned int IBO = 0;
	uint64_t TotalDraws = 0;
};

