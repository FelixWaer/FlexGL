#include "RenderManager.h"

#include <glad/glad.h>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <glm/ext/matrix_clip_space.hpp>

#include "Model.h"
#include "../Engine/EngineManager.h"

void RenderManager::init_RenderManager()
{
	load_ShadersFromFolder();
	load_MeshesFromFolder();
	load_TexturesFromFolder();

	MaterialMap[tempBasicMaterial].HasTexture = true;
	MaterialMap[tempBasicMaterial].Shininess = 64.f;
	MaterialMap[tempBasicMaterial].SpecularStrength = 0.5f;
}

void RenderManager::cleanup_RenderManager()
{
	for (auto& shader : ShaderMap)
	{
		shader.second.delete_Shader();
	}
	for (auto& mesh : MeshMap)
	{
		mesh.second.delete_Buffer();
	}
	for (auto texture : TextureMap)
	{
		texture.second.delete_Texture();
	}
}

void RenderManager::render_Scene(SceneManager* sceneToRender)
{
	Shader& shaderUsed = ShaderMap[tempShaderName];
	shaderUsed.use_Shader();

	shaderUsed.send_Vec3("CameraPos", sceneToRender->get_SceneCamera()->get_CameraPosition());
	shaderUsed.send_Vec3("LightPos", sceneToRender->get_SceneLights()[0]->get_LightPosition());
	shaderUsed.send_Vec3("LightColor", sceneToRender->get_SceneLights()[0]->get_LightColor());

	for (Model* model : sceneToRender->get_SceneModels())
	{
		if (model->is_ModelHidden() == true)
		{
			continue;
		}

		Material& modelMaterial = MaterialMap[model->get_ModelMaterialName()];

		if (MeshMap.contains(model->get_ModelMeshName()) == false)
		{
			continue;
		}

		if (modelMaterial.HasTexture == true && TextureMap.contains(modelMaterial.TextureName) == true)
		{
			TextureMap[modelMaterial.TextureName].use_Texture();
		}

		glm::mat4 modelMatrix = glm::perspective(glm::radians(45.0f),
			EngineManager::get()->get_AspectRatio(), 0.1f, 400.f) * sceneToRender->get_SceneCamera()->get_CameraView() * model->get_ModelMatrix();
		shaderUsed.send_Matrix("PositionMatrix", model->get_ModelMatrix());
		shaderUsed.send_Matrix("ModelMatrix", modelMatrix);
		shaderUsed.send_Bool("HasTexture", modelMaterial.HasTexture);
		shaderUsed.send_Float("Shininess", modelMaterial.Shininess);
		shaderUsed.send_Float("SpecularStrength", modelMaterial.SpecularStrength);

		render_Model(MeshMap[model->get_ModelMeshName()]);
	}
}

void RenderManager::load_ShadersFromFolder()
{
	for (const auto& file : std::filesystem::directory_iterator("Shader"))
	{
		std::string FileName;

		size_t ehm = file.path().string().find('\\') + 1;
		int ahm = file.path().string().length() - (ehm + file.path().extension().string().size());
		FileName = file.path().string().substr(ehm, ahm);

		if (file.path().extension() == ".vert")
		{
			ShaderMap[FileName].set_VertexShaderPath(file.path().string());
		}
		else if (file.path().extension() == ".frag")
		{
			ShaderMap[FileName].set_FragmentShaderPath(file.path().string());
		}
	}

	std::string ShaderName;
	for (auto& shader : ShaderMap)
	{
		ShaderName = shader.first;
		shader.second.init_Shader();
	}

	tempShaderName = ShaderName;
}

void RenderManager::load_MeshesFromFolder()
{
	for (const auto& file : std::filesystem::directory_iterator("Models"))
	{
		std::string FileName;

		size_t ehm = file.path().string().find('\\') + 1;
		int ahm = file.path().string().length() - (ehm + file.path().extension().string().size());
		FileName = file.path().string().substr(ehm, ahm);

		if (MeshMap.contains(FileName) == true)
		{
			continue;
		}

		if (file.path().extension() == ".obj")
		{
			MeshMap[FileName].load_MeshObj(file.path().string());
		}
		else if (file.path().extension() == ".txt")
		{
			MeshMap[FileName].load_MeshTxt(file.path().string());
		}

		std::cout << FileName << " : Mesh loaded" << std::endl;
	}

	if (MeshMap.contains("Cube") == false)
	{
		MeshMap["Cube"].create_CubeMesh();
	}
}

void RenderManager::load_TexturesFromFolder()
{
	for (const auto& file : std::filesystem::directory_iterator("Textures"))
	{
		std::string FileName;

		size_t ehm = file.path().string().find('\\') + 1;
		int ahm = file.path().string().length() - (ehm + file.path().extension().string().size());
		FileName = file.path().string().substr(ehm, ahm);

		if (file.path().extension() == ".png" && TextureMap.contains(FileName) == false)
		{
			TextureMap[FileName].load_Texture(file.path().string());
			std::cout << FileName << " : Texture loaded" << std::endl;
		}
	}
}

void RenderManager::render_Model(Mesh& meshToRender)
{
	meshToRender.bind_VAOBuffer();

	glDrawElements(GL_TRIANGLES, meshToRender.Triangles.size() * 3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

