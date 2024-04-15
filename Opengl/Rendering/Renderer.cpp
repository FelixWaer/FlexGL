#include "Renderer.h"

#include "Model.h"

Renderer* Renderer::get()
{
	if (RendererPtr == nullptr)
	{
		RendererPtr = new Renderer;
		return RendererPtr;
	}
	return RendererPtr;
}

void Renderer::init_Renderer()
{
	load_Model(FilePathModel, SphereLine);
	create_Cube(Cube, glm::vec3(1.f, 0.f, 0.f));
	create_SphereLines(DebugSphere, 1.f, glm::vec3(1.f, 0.f, 0.f));
}
