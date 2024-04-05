#pragma once
#include <string>

#include "glad/glad.h"

namespace FXGL
{

	class Shader
	{
	public:
		Shader() = default;
		~Shader();

		void init_Shader();
		void set_ShaderPath(const std::string& vertexPath, const std::string& fragmentPath);

		unsigned int ShaderProgram;
	private:
		std::string VertexShaderPath;
		std::string FragmentShaderPath;

		void cleanup_Shader();
		static std::string load_Shader(const std::string& filePath);
	};
}

