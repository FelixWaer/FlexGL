#pragma once

#include <string>

#include "Mesh.h"

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
private:
	static inline Renderer* RendererPtr;

	std::string FilePathModel = "Models/Spiral Points";
};

