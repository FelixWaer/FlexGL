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
	create_Cube(LightCube, glm::vec3(1.f), true);
	create_SphereLines(DebugSphere, 1.f, glm::vec3(1.f, 0.f, 0.f));
	TestLoadMesh.load_Model(FilePathModel2.c_str());

	TestTexture.load_Texture(texturePath);
	TreeTexture.load_Texture(TreeTexturePath);
	SkyboxTexture.load_CubeMapTexture(SkyboxPaths);
}
