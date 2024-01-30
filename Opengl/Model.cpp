#include "Model.h"

#include <iostream>
#include <fstream>

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
			float x, y, z, r, g, b;
			file >> x >> y >> z >> r >> g >> b;
			Vertices.emplace_back(x, y, z, r, g, b);

		} 
	}

}
