#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
	Shader() = default;

	void init_Shader();
	void delete_Shader();
	void use_Shader();

	void set_ShaderPath(const std::string& vertexPath, const std::string& fragmentPath);
	void set_VertexShaderPath(const std::string& filePath);
	void set_FragmentShaderPath(const std::string& filePath);

	void send_Matrix(const char* variableName, const glm::mat4& data) const;
	void send_Vec3(const char* variableName, const glm::vec3& data) const;
	void send_Bool(const char* variableName, bool data) const;
	void send_Float(const char* variabelName, float data) const;

private:
	unsigned int ShaderProgram;
	std::string VertexShaderPath;
	std::string FragmentShaderPath;

	static std::string load_Shader(const std::string& filePath);
};
