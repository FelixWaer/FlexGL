#include "Model.h"

#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

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
	}

	glm::mat4 Model::get_ModelMatrix() const
	{
		return glm::translate(glm::mat4(1.f), ModelPosition);
	}

	Line::Line()
	{
		LineMatrix = glm::mat4(1.f);
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
	}
}
