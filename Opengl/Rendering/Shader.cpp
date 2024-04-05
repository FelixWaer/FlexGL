#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

FXGL::Shader::~Shader()
{
    cleanup_Shader();
}

void FXGL::Shader::init_Shader()
{
    std::string VertexText = load_Shader(VertexShaderPath);
    const char* VertextShaderText = VertexText.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertextShaderText, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    std::string FragText = load_Shader(FragmentShaderPath);
    const char* FragmentShaderText = FragText.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShaderText, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);
    // check for linking errors
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void FXGL::Shader::set_ShaderPath(const std::string& vertexPath, const std::string& fragmentPath)
{
	VertexShaderPath = vertexPath;
	FragmentShaderPath = fragmentPath;
}

void FXGL::Shader::cleanup_Shader()
{
    glDeleteProgram(ShaderProgram);
}

std::string FXGL::Shader::load_Shader(const std::string& filePath)
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
