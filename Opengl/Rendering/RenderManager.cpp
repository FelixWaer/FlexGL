#include "RenderManager.h"

#include <glad/glad.h>

#include <filesystem>
#include <thread>
#include <iostream>
#include <fstream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Model.h"
#include "ModelCreation.h"
#include "../Components/CameraComponent.h"
#include "../Components/ComponentHandler.h"
#include "../Components/ParticleComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Engine/EngineManager.h"
#include "../FlexLibrary/FlexTimer/Flextimer.h"
#include "../GameObjects/Entity.h"

void calculate_ParticleMatrices(Mesh& instancedMesh, glm::vec3& cameraPos, std::vector<glm::vec3>& particlePositions, int start, int end)
{
	for (int i = start; i < end; i++)
	{
		//glm::vec3 direction = particlePositions[i] - cameraPos;

		//float theta = glm::atan(direction.x, direction.z);
		//float distance2D = glm::sqrt(direction.x * direction.x + direction.z * direction.z);
		//float phi = glm::atan(direction.y, distance2D);

		glm::mat4 renderMatrix = glm::translate(glm::mat4(1.f), particlePositions[i]);
		//renderMatrix = glm::rotate(renderMatrix, -phi, glm::vec3(1.f, 0.f, 0.f));
		//renderMatrix = glm::rotate(renderMatrix, theta, glm::vec3(0.f, 1.f, 0.f));
		renderMatrix = glm::scale(renderMatrix, glm::vec3(0.05f));

		instancedMesh.Matrices.emplace_back(renderMatrix);
	}
}

void RenderManager::init_RenderManager()
{
	load_ShadersFromFolder();
	load_MeshesFromFolder();
	//load_TexturesFromFolder();

	MaterialMap[tempBasicMaterial].HasTexture = false;
	MaterialMap[tempBasicMaterial].TextureName = "Atlas";
	MaterialMap[tempBasicMaterial].Shininess = 64.f;
	MaterialMap[tempBasicMaterial].SpecularStrength = 0.5f;

	MaterialMap[tempObjectMaterial].HasTexture = true;
	MaterialMap[tempObjectMaterial].TextureName = "Barrel";

	MaterialMap[tempPlacementMaterial].HasTexture = true;
	MaterialMap[tempPlacementMaterial].Transparency = 0.5f;
	MaterialMap[tempPlacementMaterial].TextureName = "Barrel";

	MaterialMap[tempEnemyMaterial].HasTexture = false;
	MaterialMap[tempEnemyMaterial].ColorHue = glm::vec3(1.f, 0.f, 0.f);

	MaterialMap[tempPlayerMaterial].HasTexture = false;
	MaterialMap[tempPlayerMaterial].ColorHue = glm::vec3(0.f, 0.f, 1.f);

	MaterialMap[tempBulletMaterial].HasTexture = false;
	MaterialMap[tempBulletMaterial].ColorHue = glm::vec3(1.f, 0.f, 1.f);
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
	FlexTimer timer("Render Time");

	if (Render2D == true)
	{
		Shader& shaderUsed = ShaderMap["Flex2DShader"];
		shaderUsed.use_Shader();

		if (EngineManager::get()->get_ActiveScene()->get_ComponentManager().check_IfHandlerExists<SpriteComponent>() == false ||
			EngineManager::get()->get_ActiveScene()->get_ComponentManager().check_IfHandlerExists<TransformComponent>() == false)
		{
			return;
		}
		ComponentHandler<SpriteComponent>* spriteComponents = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<SpriteComponent>();
		ComponentHandler<TransformComponent>* transComponents = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<TransformComponent>();

		for (auto& element : spriteComponents->IndexMap)
		{
			if (spriteComponents->Components[element.second].Render == false)
			{
				continue;
			}

			Material& modelMaterial = MaterialMap[spriteComponents->Components[element.second].MaterialName];

			if (modelMaterial.HasTexture == true && TextureMap.contains(modelMaterial.TextureName) == true)
			{
				TextureMap[modelMaterial.TextureName].use_Texture();
			}

			glm::mat4 ProjectionMatrix = glm::ortho(0.f, static_cast<float>(EngineManager::get()->get_WindowWidth()),
				static_cast<float>(EngineManager::get()->get_WindowHeight()), 0.0f, -1.f, 1.f);

			shaderUsed.send_Matrix("ModelMatrix", transComponents->get_Component(element.first).Matrix);

			shaderUsed.send_Bool("HasTexture", modelMaterial.HasTexture);
			shaderUsed.send_Float("Transparency", modelMaterial.Transparency);
			shaderUsed.send_Vec3("ColorHue", modelMaterial.ColorHue);

			render_Model(MeshMap[spriteComponents->Components[element.second].SpriteName]);
		}

		return;
	}

	Shader& shaderUsed = ShaderMap["FlexShader"];
	shaderUsed.use_Shader();

	if (EngineManager::get()->get_ActiveScene()->get_ComponentManager().check_IfHandlerExists<SpriteComponent>() == false ||
		EngineManager::get()->get_ActiveScene()->get_ComponentManager().check_IfHandlerExists<TransformComponent>() == false)
	{
		return;
	}

	ComponentHandler<SpriteComponent>* spriteComponents = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<SpriteComponent>();
	ComponentHandler<TransformComponent>* transComponents = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<TransformComponent>();

	glm::mat4 cameraView = glm::lookAt(ActiveCamera->get_Component<PositionComponent>().Position, ActiveCamera->get_Component<PositionComponent>().Position 
		+ ActiveCamera->get_Component<CameraComponent>().CameraDirection, ActiveCamera->get_Component<CameraComponent>().CameraUp);

	glm::mat4 test = ActiveCamera->get_Component<TransformComponent>().Matrix;

	shaderUsed.send_Vec3("CameraPos", ActiveCamera->get_Component<PositionComponent>().Position);
	shaderUsed.send_Vec3("LightPos", sceneToRender->get_SceneLights()[0]->get_LightPosition());
	shaderUsed.send_Vec3("LightColor", sceneToRender->get_SceneLights()[0]->get_LightColor());
	shaderUsed.send_Bool("InstancedRendering", false);

	for (auto& element : spriteComponents->IndexMap)
	{

		if (spriteComponents->Components[element.second].Render == false)
		{
			continue;
		}

		Material& modelMaterial = MaterialMap[spriteComponents->Components[element.second].MaterialName];

		if (modelMaterial.HasTexture == true && TextureMap.contains(modelMaterial.TextureName) == true)
		{
			TextureMap[modelMaterial.TextureName].use_Texture();
		}

		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.f), EngineManager::get()->get_AspectRatio(), 0.1f, 400.f);
		ProjectionMatrix *= cameraView * transComponents->get_Component(element.first).Matrix;

		shaderUsed.send_Matrix("PositionMatrix", transComponents->get_Component(element.first).Matrix);
		shaderUsed.send_Matrix("ModelMatrix", ProjectionMatrix);

		shaderUsed.send_Bool("HasTexture", modelMaterial.HasTexture);
		shaderUsed.send_Float("Shininess", modelMaterial.Shininess);
		shaderUsed.send_Float("SpecularStrength", modelMaterial.SpecularStrength);

		render_Model(MeshMap[spriteComponents->Components[element.second].SpriteName]);
	}
	//auto start = std::chrono::high_resolution_clock::now();

	render_ParticleSystem();

	//auto end = std::chrono::high_resolution_clock::now();
	//std::cout << "instanced time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start) << std::endl;
}

Mesh& RenderManager::get_Mesh(std::string meshName)
{
	if (MeshMap.contains(meshName) == true)
	{
		return MeshMap[meshName];
	}

	Mesh tempMesh;

	return tempMesh;
}

void RenderManager::add_Mesh(Mesh& newMesh, std::string meshName)
{
	if (MeshMap.contains(meshName) == false)
	{
		MeshMap[meshName] = newMesh;
		std::cout << "Added new mesh: " << meshName << std::endl;
	}
}

Material& RenderManager::get_Material(std::string materialName)
{
	if (MaterialMap.contains(materialName) == true)
	{
		return MaterialMap[materialName];
	}

	Material tempMesh;

	return tempMesh;
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

void RenderManager::render_ParticleSystem()
{
	FlexTimer timer("Particle System");
	Shader& shaderUsed = ShaderMap["FlexShader"];
	shaderUsed.use_Shader();

	ComponentHandler<ParticleComponent>* particleComponents = EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<ParticleComponent>();

	glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.f), EngineManager::get()->get_AspectRatio(), 0.1f, 400.f);
	glm::mat4 cameraView = glm::lookAt(ActiveCamera->get_Component<PositionComponent>().Position, ActiveCamera->get_Component<PositionComponent>().Position
		+ ActiveCamera->get_Component<CameraComponent>().CameraDirection, ActiveCamera->get_Component<CameraComponent>().CameraUp);

	Material& modelMaterial = MaterialMap[tempBasicMaterial];
	glm::mat4 ModelMatrix = ProjectionMatrix * cameraView;

	MeshMap["Cube"].Matrices.clear();

	glm::vec3 cameraPos = ActiveCamera->get_Component<PositionComponent>().Position;

	int start = 0;
	int middle = particleComponents->Components[0].ParticlePositions.size() / 2;
	int end = particleComponents->Components[0].ParticlePositions.size();

	//std::thread jaja(calculate_ParticleMatrices, std::ref(MeshMap["Cube"]), std::ref(cameraPos), std::ref(particleComponents->Components[0].ParticlePositions), start, middle);
	//std::thread neinei(calculate_ParticleMatrices, std::ref(MeshMap["Cube"]), std::ref(cameraPos), std::ref(particleComponents->Components[0].ParticlePositions), middle, end);

	//jaja.join();
	//neinei.join();

	calculate_ParticleMatrices(MeshMap["Cube"], cameraPos, particleComponents->Components[0].ParticlePositions, start, end);

	MeshMap["Cube"].rebind_InstancedBuffer(GL_STATIC_DRAW);

	shaderUsed.send_Bool("InstancedRendering", true);

	shaderUsed.send_Matrix("ModelMatrix", ModelMatrix);

	shaderUsed.send_Bool("HasTexture", modelMaterial.HasTexture);
	shaderUsed.send_Float("Shininess", modelMaterial.Shininess);
	shaderUsed.send_Float("SpecularStrength", modelMaterial.SpecularStrength);

	render_ModelInstanced(MeshMap["Cube"], particleComponents->Components[0].ParticlePositions.size());
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
	if (MeshMap.contains("Square") == false)
	{
		FLXModel::create_Square(MeshMap["Square"]);
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

void RenderManager::render_ModelInstanced(Mesh& meshToRender, int totalDrawCalls)
{
	meshToRender.bind_VAOBuffer();

	glDrawElementsInstanced(GL_TRIANGLES, meshToRender.Triangles.size() * 3, GL_UNSIGNED_INT, 0, totalDrawCalls);

	glBindVertexArray(0);
}