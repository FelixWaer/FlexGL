#include "Model.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

#include "EngineManager.h"
#include "GameObject.h"
Vertex::Vertex(float x_, float y_, float z_, const glm::vec3& color)
{
	x = x_;
	y = y_;
	z = z_;

	RGB = color;
}

void Model::init_Model()
{
	ModelScale = glm::vec3(1.f);
	EngineManager::TheEngineManager->add_ToModelHandler(this);
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
	glm::vec3 color;
	while (file.eof() == false)
	{
		if (isdigit(file.peek()) != true)
		{
			std::string line;
			std::getline(file, line);
		}
		float x, y, z, r, g, b;
		file >> x >> y >> z >> r >> g >> b;

		color = glm::vec3(r, g, b);

		Vertices.emplace_back(x, y, z, color);
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
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), Indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Model::bind_ToGameObject(GameObject* GO)
{
	AttachedModelPosition = GO->get_GameObjectPositionPtr();
}

void Model::attach_ToPosition(glm::vec3* attachedPosition)
{
	AttachedModelPosition = attachedPosition;
}

void Model::hide_Model(bool hidingModel)
{
	HidingModel = hidingModel;
}

void Model::set_ModelPosition(glm::vec3 newPosition)
{
	ModelPosition = newPosition;
}

void Model::scale_Model(glm::vec3 newScale)
{
	ModelScale = newScale;
}

void Model::rotate_Model(glm::vec3 newRotation)
{
	ModelRotation = newRotation;
}

void Model::draw_ModelAsLines(bool drawModelLines)
{
	DrawLines = drawModelLines;
}

void Model::draw_Model()
{
	if (HidingModel == true)
	{
		return;
	}

	if (DrawLines == true)
	{
		glBindVertexArray(VAO);

		glDrawElements(GL_LINE_STRIP, Indices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		return;
	}

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

glm::mat4 Model::get_ModelMatrix() const
{
	glm::scale(glm::translate(glm::mat4(1.f), ModelPosition), ModelScale);
	if (AttachedModelPosition == nullptr)
	{
		return glm::scale(glm::translate(glm::mat4(1.f), ModelPosition) * glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f)), ModelScale);
	}

	return glm::scale(glm::translate(glm::mat4(1.f), *AttachedModelPosition) * glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f)), ModelScale);
}

void Model::cleanup_Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Line::Line(bool isLine)
{
	IsLine = isLine;
}

void Line::init_LineModel()
{
	EngineManager::TheEngineManager->add_ToLineModelHandler(this);
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
	glm::vec3 color;
	while (file.eof() == false)
	{
		if (isdigit(file.peek()) != true)
		{
			std::string line;
			std::getline(file, line);
		}
		float x, y, z, r, g, b;
		file >> x >> y >> z >> r >> g >> b;

		color = glm::vec3(r, g, b);
		Vertices.emplace_back(x, y, z, color);
	}

	bind_Buffer();
}

void Line::bind_Buffer()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void Line::draw_Line()
{
	if (HidingModel == true)
	{
		return;
	}
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
	if (AttachedLineModelPosition == nullptr)
	{
		return glm::translate(glm::mat4(1.f), LineModelPosition);
	}
	return glm::translate(glm::mat4(1.f), *AttachedLineModelPosition);
}

void Line::set_Location(glm::vec3 posVector)
{
	LineModelPosition = posVector;
}

void Line::cleanup_LineModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Line::bind_ToGameObject(GameObject* GO)
{
	AttachedLineModelPosition = GO->get_GameObjectPositionPtr();
}

void Line::attach_ToPosition(glm::vec3* attachedPosition)
{
	AttachedLineModelPosition = attachedPosition;
}

void Line::hide_LineModel(bool hidingModel)
{
	HidingModel = hidingModel;
}

void create_Cube(Model& model, const glm::vec3& color)
{
	model.Vertices.emplace_back(-0.5f, 0.5f, 0.5f, color);
	model.Vertices.emplace_back(-0.5f, -0.5f, 0.5f, color);
	model.Vertices.emplace_back(0.5f, -0.5f, 0.5f, color);
	model.Vertices.emplace_back(0.5f, 0.5f, 0.5f, color);

	model.Vertices.emplace_back(-0.5f, 0.5f, -0.5f, color);
	model.Vertices.emplace_back(-0.5f, -0.5f, -0.5f, color);
	model.Vertices.emplace_back(0.5f, -0.5f, -0.5f, color);
	model.Vertices.emplace_back(0.5f, 0.5f, -0.5f, color);

	model.Indices.emplace_back(0);
	model.Indices.emplace_back(1);
	model.Indices.emplace_back(2);

	model.Indices.emplace_back(2);
	model.Indices.emplace_back(3);
	model.Indices.emplace_back(0);

	model.Indices.emplace_back(3);
	model.Indices.emplace_back(2);
	model.Indices.emplace_back(6);

	model.Indices.emplace_back(6);
	model.Indices.emplace_back(7);
	model.Indices.emplace_back(3);

	model.Indices.emplace_back(7);
	model.Indices.emplace_back(6);
	model.Indices.emplace_back(5);

	model.Indices.emplace_back(5);
	model.Indices.emplace_back(4);
	model.Indices.emplace_back(7);

	model.Indices.emplace_back(4);
	model.Indices.emplace_back(5);
	model.Indices.emplace_back(1);

	model.Indices.emplace_back(1);
	model.Indices.emplace_back(0);
	model.Indices.emplace_back(4);

	model.Indices.emplace_back(0);
	model.Indices.emplace_back(3);
	model.Indices.emplace_back(7);

	model.Indices.emplace_back(7);
	model.Indices.emplace_back(4);
	model.Indices.emplace_back(0);

	model.Indices.emplace_back(1);
	model.Indices.emplace_back(2);
	model.Indices.emplace_back(6);

	model.Indices.emplace_back(6);
	model.Indices.emplace_back(5);
	model.Indices.emplace_back(1);

	model.bind_Buffer();
}

void create_SphereLines(Line& lineModel, float radius, const glm::vec3& color)
{
	float degrees =22.5f;
	for (int i = 0; i < 18; i++)
	{
		lineModel.Vertices.emplace_back(radius * sin(glm::radians(degrees*i)), radius * cos(glm::radians(degrees*i)), 0.f, color);
	}
	for (int i = 0; i < 21; i++)
	{
		lineModel.Vertices.emplace_back(0.f, radius * cos(glm::radians(degrees*i)), radius * sin(glm::radians(degrees*i)), color);
	}
	for (int i = 0; i < 18; i++)
	{
		lineModel.Vertices.emplace_back(radius * sin(glm::radians(degrees*i)), 0.f, radius * cos(glm::radians(degrees*i)), color);
	}

	lineModel.bind_Buffer();
}

void create_BoxLines(Line& lineModel, float height, float width, float depth, const glm::vec3& color)
{
	lineModel.Vertices.emplace_back(width / 2, height / 2, depth / 2, color);
	lineModel.Vertices.emplace_back(-width / 2, height / 2, depth / 2, color);

	lineModel.Vertices.emplace_back(width / 2, -height / 2, depth / 2, color);
	lineModel.Vertices.emplace_back(-width / 2, -height / 2, depth / 2, color);

	lineModel.Vertices.emplace_back(width / 2, height / 2, -depth / 2, color);
	lineModel.Vertices.emplace_back(-width / 2, height / 2, -depth / 2, color);

	lineModel.Vertices.emplace_back(width / 2, -height / 2, -depth / 2, color);
	lineModel.Vertices.emplace_back(-width / 2, -height / 2, -depth / 2, color);

	lineModel.bind_Buffer();
}
