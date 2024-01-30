#pragma once
#include <string>

#include "glad/glad.h"

namespace FXGL
{

	class Shader
	{
	public:
		Shader() = default;

		static std::string load_Shader(std::string &filePath);
	};
}

