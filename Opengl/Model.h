#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace FXGL
{
	struct Vertex
	{
	public:
		Vertex() = default;
		Vertex(float x, float y, float z, float r, float g, float b);

		float x, y, z, r, g, b;
	};

	class Model
	{
	public:
		Model() = default;

		std::vector<Vertex> Vertices;
		glm::mat4 ModelMatrix;

		void load_Model(std::string& filePath);
	};
}

