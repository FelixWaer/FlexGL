#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::string FXGL::Shader::load_Shader(std::string& filePath)
{
	std::stringstream tempShader;
	std::string returnShader;

	std::ifstream file;
	file.open(filePath);
	if (file.is_open() == false)
	{
		std::cout << "file could not open!" << std::endl;
	}
	tempShader << file.rdbuf();

	returnShader = tempShader.str();

	return returnShader;
}
