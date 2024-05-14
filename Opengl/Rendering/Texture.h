#pragma once

class Texture
{
public:
	Texture() = default;

	void load_Texture(const char* texturePath);
	void use_Texture();
private:
	unsigned int TextureData;
};

