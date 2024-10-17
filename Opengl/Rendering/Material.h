#pragma once
#include <string>
#include <glm/vec3.hpp>

class Material
{
public:
	std::string ShaderName = "FlexShader";
	std::string TextureName = "cover4";

	bool HasTexture = true;
	float Transparency = 1.f;
	float Shininess = 32.f;
	float SpecularStrength = 0.2f;
	glm::vec3 ColorHue = glm::vec3(0.f);
};

