#pragma once

#include <string>

#include "Mesh.h"
#include "Texture.h"

class Renderer
{
public:
	Renderer() = default;

	static Renderer* get();
	void init_Renderer();

	Mesh SphereLine;
	Mesh Cube;
	Mesh LightCube;
	Mesh Line;
	Mesh DebugSphere;
	Mesh TestLoadMesh;

	Texture TestTexture;
	Texture TreeTexture;
	Texture SkyboxTexture;

private:
	static inline Renderer* RendererPtr;

	std::string FilePathModel = "Models/Spiral Points";
	std::string FilePathModel2 = "Models/Rock.Obj";
	std::vector<std::string> SkyboxPaths = {
		"Textures/right.jpg",
		"Textures/left.jpg",
		"Textures/up.jpg",
		"Textures/down.jpg",
		"Textures/front.jpg",
		"Textures/back.jpg"
	};
	const char* texturePath = "Textures/grass4_wind.jpg";
	const char* TreeTexturePath = "Textures/cover4.png";
};

