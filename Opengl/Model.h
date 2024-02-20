#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "glad/glad.h"

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

		unsigned int VAO;
		std::vector<Vertex> Vertices;

		Line();
		void load_LineModel(std::string& filePath);
		void draw_Line();

		glm::mat4 get_LineMatrix() const;
		void set_Location(glm::vec3 posVector);
	private:
		glm::vec3 LinePosition;
		unsigned int VBO;

		void bind_Buffer();
	};
}

