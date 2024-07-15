#pragma once
#include <string>
#include <glm/glm.hpp>

#include "glad/glad.h"

class Shader
{
public:
	Shader() = default;
	~Shader();

	void init_Shader();
	void set_ShaderPath(const std::string& vertexPath, const std::string& fragmentPath);

	void send_Matrix(const char* variableName, const glm::mat4& data) const;
	void send_Vec3(const char* variableName, const glm::vec3& data) const;
	void send_Bool(const char* variableName, bool data) const;

	unsigned int ShaderProgram;
private:
	std::string VertexShaderPath;
	std::string FragmentShaderPath;

	void cleanup_Shader();
	static std::string load_Shader(const std::string& filePath);
};
