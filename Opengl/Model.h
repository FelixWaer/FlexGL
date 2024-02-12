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
		Model();

		std::vector<Vertex> Vertices;
		std::vector<int> Indices;
		glm::vec3 ModelPosition;

		void load_Model(std::string& filePath);
		glm::mat4 get_ModelMatrix() const;
	};

	class Line
	{
	public:
		Line();

		std::vector<Vertex> Vertices;
		glm::mat4 LineMatrix;

		void load_LineModel(std::string& filePath);
	};
}

