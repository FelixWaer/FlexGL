#include "Model.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

#include "EngineManager.h"

namespace FXGL
{
	Vertex::Vertex(float x_, float y_, float z_, float r_, float g_, float b_)
	{
		x = x_;
		y = y_;
		z = z_;
		r = r_;
		g = g_;
		b = b_;
	}

	Model::Model()
	{
		ModelPosition = glm::vec3(0.f, 0.f, 0.f);

	}

	Model::~Model()
	{
		//cleanup_Model();
	}

	void Model::load_Model(std::string& filePath)
	{
		std::ifstream file;
		file.open(filePath);
		std::vector<float> test;
		if (file.is_open() == false)
		{
			std::cout << "could not open model file!" << std::endl;
			return;
		}

		std::vector<float> vertexData;
		int i = 0;
		float data;
		while (file.eof() == false)
		{
			if (isdigit(file.peek()) != true)
			{
				std::string line;
				std::getline(file, line);
			}
			float x, y, z, r, g, b;
			file >> x >> y >> z >> r >> g >> b;


			Vertices.emplace_back(x, y, z, r, g, b);
		}

		bind_Buffer();
	}

	void Model::bind_Buffer()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(FXGL::Vertex), Vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FXGL::Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FXGL::Vertex), (void*)12);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void Model::draw_Model()
	{
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	glm::mat4 Model::get_ModelMatrix() const
	{
		return glm::translate(glm::mat4(1.f), ModelPosition);
	}

	void Model::cleanup_Model()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	Line::Line(bool isLine)
	{
		LinePosition = glm::vec3(0.f);
		IsLine = isLine;

	}

	Line::~Line()
	{
		//cleanup_LineModel();
	}

	void Line::load_LineModel(std::string& filePath)
	{
		std::ifstream file;
		file.open(filePath);
		std::vector<float> test;
		if (file.is_open() == false)
		{
			std::cout << "could not open model file!" << std::endl;
			return;
		}

		std::vector<float> vertexData;
		int i = 0;
		float data;
		while (file.eof() == false)
		{
			if (isdigit(file.peek()) != true)
			{
				std::string line;
				std::getline(file, line);
			}
			float x, y, z, r, g, b;
			file >> x >> y >> z >> r >> g >> b;


			Vertices.emplace_back(x, y, z, r, g, b);
		}

		bind_Buffer();
	}

	void Line::bind_Buffer()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(FXGL::Vertex), Vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FXGL::Vertex), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FXGL::Vertex), (void*)12);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}

	void Line::draw_Line()
	{
		glBindVertexArray(VAO);
		if (IsLine == true)
		{
			glDrawArrays(GL_LINE_STRIP, 0, Vertices.size());
		}
		else
		{
			glDrawArrays(GL_POINTS, 0, Vertices.size());
		}

		glBindVertexArray(0);
	}

	glm::mat4 Line::get_LineMatrix() const
	{
		return glm::translate(glm::mat4(1.f), LinePosition);
	}

	void Line::set_Location(glm::vec3 posVector)
	{
		LinePosition = posVector;
	}

	void Line::cleanup_LineModel()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}
