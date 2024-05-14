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
	Mesh Line;
	Mesh DebugSphere;
	Mesh TestLoadMesh;

	Texture TestTexture;
private:
	static inline Renderer* RendererPtr;

	std::string FilePathModel = "Models/Spiral Points";
	std::string FilePathModel2 = "Models/pen.obj";
	const char* texturePath = "Textures/cover4.png";
};

