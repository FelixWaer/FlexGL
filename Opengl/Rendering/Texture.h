#pragma once

#include <string>
#include <vector>

class Texture
{
public:
	Texture() = default;

	void delete_Texture();

	void load_Texture(const std::string& filePath);
	void use_Texture();

	void load_CubeMapTexture(const std::vector<std::string>& texturePaths);
	void use_CubeMapTexture();
private:
	unsigned int TextureID;
};

