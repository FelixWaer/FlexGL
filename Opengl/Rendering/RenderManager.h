#pragma once
#include <string>
#include <unordered_map>

#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

class SceneManager;

class RenderManager
{
public:
	void init_RenderManager();
	void cleanup_RenderManager();
	void render_Scene(SceneManager* sceneToRender);

private:
	std::unordered_map<std::string, Shader> ShaderMap;
	std::unordered_map<std::string, Mesh> MeshMap;
	std::unordered_map<std::string, Texture> TextureMap;
	std::unordered_map<std::string, Material> MaterialMap;

	std::string tempShaderName = " ";
	std::string tempBasicMaterial = "BasicMaterial";

	void load_ShadersFromFolder();
	void load_MeshesFromFolder();
	void load_TexturesFromFolder();

	void render_Model(Mesh& meshToRender);
};

