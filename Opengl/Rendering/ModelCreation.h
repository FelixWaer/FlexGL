#pragma once
#include <string>

#include <glm/glm.hpp>

class Mesh;

namespace FLXModel
{
	void create_Cube(Mesh& model, const glm::vec3& color, bool reverseNormals = false);

	void create_Square(Mesh& mesh);

	void create_Grid(Mesh& mesh, int size);

	void create_SphereLines(Mesh& lineModel, float radius, const glm::vec3& color);

	void create_BoxLines(Mesh& lineModel, float height, float width, float depth, const glm::vec3& color);
}