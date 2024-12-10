#pragma once
#include <string>
#include <unordered_map>

#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

class SceneManager;
class Entity;

class RenderManager
{
public:
	void init_RenderManager();
	void cleanup_RenderManager();
	void render_Scene(SceneManager* sceneToRender);
	Mesh& get_Mesh(std::string meshName);
	void add_Mesh(Mesh& newMesh, std::string meshName);
	Material& get_Material(std::string materialName);
	bool Render2D = false;
	
	Entity* ActiveCamera = nullptr;
private:

	std::unordered_map<std::string, Shader> ShaderMap;
	std::unordered_map<std::string, Mesh> MeshMap;
	std::unordered_map<std::string, Texture> TextureMap;
	std::unordered_map<std::string, Material> MaterialMap;

	std::string tempShaderName = " ";
	std::string tempBasicMaterial = "BasicMaterial";
	std::string tempObjectMaterial = "ObjectMaterial";
	std::string tempPlacementMaterial = "PlacementMaterial";
	std::string tempEnemyMaterial = "EnemyMaterial";
	std::string tempPlayerMaterial = "PlayerMaterial";
	std::string tempBulletMaterial = "BulletMaterial";

	void load_ShadersFromFolder();
	void load_MeshesFromFolder();
	void load_TexturesFromFolder();

	void render_ParticleSystem();

	void render_Model(Mesh& meshToRender);
	void render_ModelInstanced(Mesh& meshToRender, int totalDrawCalls);
};

