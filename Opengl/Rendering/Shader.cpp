#include "Shader.h"

#include "glad/glad.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

void Shader::init_Shader()
{
    //Vertex Shade
    std::string VertexText = load_Shader(VertexShaderPath);
    const char* VertextShaderText = VertexText.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertextShaderText, NULL);
    glCompileShader(vertexShader);

    //Check for Vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment shader
    std::string FragText = load_Shader(FragmentShaderPath);
    const char* FragmentShaderText = FragText.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShaderText, NULL);
    glCompileShader(fragmentShader);

    //Check for Fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Create Shader Program
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);

    //Check for linking errors
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::delete_Shader()
{
    glDeleteProgram(ShaderProgram);
}

void Shader::use_Shader()
{
    glUseProgram(ShaderProgram);
}

void Shader::set_ShaderPath(const std::string& vertexPath, const std::string& fragmentPath)
{
	VertexShaderPath = vertexPath;
	FragmentShaderPath = fragmentPath;
}

void Shader::set_VertexShaderPath(const std::string& filePath)
{
    VertexShaderPath = filePath;
}

void Shader::set_FragmentShaderPath(const std::string& filePath)
{
    FragmentShaderPath = filePath;
}

void Shader::send_Matrix(const char* variableName, const glm::mat4& data) const
{
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, variableName), 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::send_Vec3(const char* variableName, const glm::vec3& data) const
{
    glUniform3fv(glGetUniformLocation(ShaderProgram, variableName), 1, glm::value_ptr(data));
}

void Shader::send_Bool(const char* variableName, bool data) const
{
    glUniform1i(glGetUniformLocation(ShaderProgram, variableName), data);
}

void Shader::send_Float(const char* variabelName, float data) const
{
    glUniform1f(glGetUniformLocation(ShaderProgram, variabelName), data);
}

std::string Shader::load_Shader(const std::string& filePath)
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
