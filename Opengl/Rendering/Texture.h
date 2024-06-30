#pragma once

#include <string>
#include <vector>

class Texture
{
public:
	Texture() = default;

	void load_Texture(const char* texturePath);
	void use_Texture();

	void load_CubeMapTexture(const std::vector<std::string>& texturePaths);
	void use_CubeMapTexture();
private:
	unsigned int TextureID;
};

