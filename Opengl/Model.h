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
		~Model();

		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
		glm::vec3 ModelPosition;

		void load_Model(std::string& filePath);
		void bind_Buffer();
		void draw_Model();
		glm::mat4 get_ModelMatrix() const;

	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		void cleanup_Model();
	};

	class Line
	{
	public:
		Line(bool isLine);
		~Line();
		
		std::vector<Vertex> Vertices;

		void load_LineModel(std::string& filePath);
		void bind_Buffer();
		void draw_Line();
		glm::mat4 get_LineMatrix() const;
		void set_Location(glm::vec3 posVector);
	private:
		glm::vec3 LinePosition;
		unsigned int VAO;
		unsigned int VBO;
		bool IsLine;

		void cleanup_LineModel();
	};
}

