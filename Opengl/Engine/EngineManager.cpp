#include "EngineManager.h"

#include <iostream>
#include <windows.h>

#include "../Rendering/Mesh.h"
#include "../Rendering/Renderer.h"
#include "Input.h"

const float SCR_WIDTH = 1920;
const float SCR_HEIGHT = 1080;

std::string FilePathVert = "Shader/Vertex_Shader.vert";
std::string FilePathFrag = "Shader/Fragment_Shader.frag";
std::string FilePathTestVert = "Shader/TestVert.vert";
std::string FilePathTestFrag = "Shader/TestFrag.frag";
std::string FilePathSkyboxShaderVert = "Shader/SkyBoxShader.vs";
std::string FilePathSkyboxShaderFrag = "Shader/SkyBoxShader.fs";

EngineManager* EngineManager::get_Engine()
{
	if (TheEngineManager == nullptr)
	{
		TheEngineManager = new EngineManager;
	}
	return TheEngineManager;
}

void EngineManager::init_Window()
{
	TheWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle window", NULL, NULL);
}

void EngineManager::init_Engine()
{
	TheShader.set_ShaderPath(FilePathVert, FilePathFrag);
	TheShader.init_Shader();
	SkyboxShader.set_ShaderPath(FilePathSkyboxShaderVert, FilePathSkyboxShaderFrag);
	SkyboxShader.init_Shader();
	Renderer::get()->init_Renderer();

	TheLight.set_LightColor(glm::vec3(1.f));
	TheLight.set_LightPosition(glm::vec3(0.f, 100.f, 0.f));
	TheLight.init_Light();

	TheGame.game_Start();

	for (GameObject* gameObject : GameObjectsToBeAdded)
	{
		GameObjectHandler.emplace_back(gameObject);
	}
	GameObjectsToBeAdded.clear();

	for (GameObject* gameObject : GameObjectHandler)
	{
		gameObject->game_Start();
	}
}

void EngineManager::tick_Engine()
{
	for (GameObject* gameObject : GameObjectsToBeAdded)
	{
		GameObjectHandler.emplace_back(gameObject);
	}
	GameObjectsToBeAdded.clear();

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	float currentFrame = static_cast<float>(glfwGetTime());
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;

	TheGame.input(TheWindow);
	check_Collision();

	TheGame.tick(DeltaTime);
	for (GameObject* gameObject  : GameObjectHandler)
	{
		gameObject->tick(DeltaTime);
	}

	glClearColor(0.f, 0.f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(10);
	glPointSize(5);

	//start skybox shader part

	if (get_Skybox() != nullptr)
	{
		glDepthMask(GL_FALSE);
		glUseProgram(SkyboxShader.ShaderProgram);

		glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), SCR_WIDTH / SCR_HEIGHT, 0.1f, 400.f);
		glm::mat4 viewMatrix = glm::mat4(glm::mat3(get_ActiveCamera().get_CameraView()));
		Renderer::get()->SkyboxTexture.use_CubeMapTexture();

		SkyboxShader.send_Matrix("Projection", projectionMatrix);
		SkyboxShader.send_Matrix("View", viewMatrix);
		get_Skybox()->draw_Model();

		glDepthMask(GL_TRUE);
	}

	//end skybox shader part

	glUseProgram(TheShader.ShaderProgram);
	TheShader.send_Vec3("CameraPos", get_ActiveCamera().get_CameraPosition());
	TheShader.send_Vec3("LightPos", TheLight.get_LightPosition());
	TheShader.send_Vec3("LightColor", TheLight.get_LightColor());

	for (Model* chunkModel : Terrain::get_Terrain()->RenderedChunks)
	{
		if (chunkModel->ModelMesh == nullptr)
		{
			continue;
		}
		glm::mat4 modelMatrix = glm::perspective(glm::radians(45.0f),
			SCR_WIDTH / SCR_HEIGHT, 0.1f, 400.f) * get_ActiveCamera().get_CameraView() * chunkModel->get_ModelMatrix();
		TheShader.send_Matrix("PositionMatrix", chunkModel->get_ModelMatrix());
		TheShader.send_Matrix("ModelMatrix", modelMatrix);
		TheShader.send_Bool("HasTexture", chunkModel->has_Texture());

		chunkModel->draw_Model();
	}

	for (auto model : ModelHandler)
	{
		if (model->ModelMesh == nullptr || model->skybox == true)
		{
			continue;
		}
		glm::mat4 modelMatrix = glm::perspective(glm::radians(45.0f),
			SCR_WIDTH / SCR_HEIGHT, 0.1f, 400.f) * get_ActiveCamera().get_CameraView() * model->get_ModelMatrix();
		TheShader.send_Matrix("PositionMatrix", model->get_ModelMatrix());
		TheShader.send_Matrix("ModelMatrix", modelMatrix);
		TheShader.send_Bool("HasTexture", model->has_Texture());

		model->draw_Model();
	}

	//std::cout << 1 / DeltaTime << std::endl;

	Input::reset_Input();
}

void EngineManager::check_Collision()
{
	if(SphereCollisionHandler.size() > 1)
	{
		for (size_t i = 0; i < SphereCollisionHandler.size(); i++)
		{
			for (size_t j = i+1; j < SphereCollisionHandler.size(); j++)
			{
				if (calculate_SphereCollision(SphereCollisionHandler[i]->get_SpherePosition(), SphereCollisionHandler[j]->get_SpherePosition(),
					SphereCollisionHandler[i]->get_SphereRadius(), SphereCollisionHandler[j]->get_SphereRadius()))
				{
					SphereCollisionHandler[i]->run_CollisionFunction(SphereCollisionHandler[j]);
					SphereCollisionHandler[j]->run_CollisionFunction(SphereCollisionHandler[i]);
				}
			}
		}
	}
	if (BoxCollisionHandler.size() > 1)
	{
		for (size_t i = 0; i < BoxCollisionHandler.size(); i++)
		{
			for (size_t j = i+1; j < BoxCollisionHandler.size(); j++)
			{
				if (calculate_BoxCollision(BoxCollisionHandler[i]->get_BoxPosition(), BoxCollisionHandler[j]->get_BoxPosition(), 
					BoxCollisionHandler[i]->BoxHeight, BoxCollisionHandler[i]->BoxWidth, BoxCollisionHandler[i]->BoxDepth,
					BoxCollisionHandler[j]->BoxHeight, BoxCollisionHandler[j]->BoxWidth, BoxCollisionHandler[j]->BoxDepth))
				{
					BoxCollisionHandler[i]->run_CollisionFunction(BoxCollisionHandler[j]);
					BoxCollisionHandler[j]->run_CollisionFunction(BoxCollisionHandler[i]);
				}
			}
		}
	}
}

void EngineManager::add_ToModelHandler(Model* modelPtr)
{
	ModelHandler.emplace_back(modelPtr);
}

void EngineManager::add_ToGameObjectHandler(GameObject* gameObjectPtr)
{
	GameObjectsToBeAdded.emplace_back(gameObjectPtr);
}

void EngineManager::add_ToSphereCollisionHandler(SphereCollision* sphereCollisionPtr)
{
	SphereCollisionHandler.emplace_back(sphereCollisionPtr);
}

void EngineManager::add_ToBoxCollisionHandler(BoxCollision* boxCollisionPtr)
{
	BoxCollisionHandler.emplace_back(boxCollisionPtr);
}

float EngineManager::get_DeltaTime()
{
	return DeltaTime;
}

void EngineManager::add_ToCameraHandler(Camera* CameraPtr)
{
	CameraHandler.emplace_back(CameraPtr);
}

void EngineManager::set_ActiveCamera(Camera* cameraPtr)
{
	ActiveCamera = cameraPtr;
}

Camera& EngineManager::get_ActiveCamera()
{
	return *ActiveCamera;
}

void EngineManager::set_Skybox(Model* skyboxModel)
{
	TheSkybox = skyboxModel;
}

Model* EngineManager::get_Skybox()
{
	return TheSkybox;
}

void EngineManager::turnOff_DebugMode(bool turnOff)
{
	for (SphereCollision* sphere : SphereCollisionHandler)
	{
		sphere->enable_SphereVisible(turnOff);
	}
	for (BoxCollision* sphere : BoxCollisionHandler)
	{
		sphere->enable_BoxVisible(turnOff);
	}
}

bool EngineManager::calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2)
{
	float distance = pow((spherePos_1.x - spherePos_2.x), 2) + pow((spherePos_1.y - spherePos_2.y), 2) + pow((spherePos_1.z - spherePos_2.z), 2);
	if (sqrt(distance) < sphereRadius_1 + sphereRadius_2)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

bool EngineManager::calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2)
{
	return (boxPos_1.x - boxWidth_1 / 2) <= (boxPos_2.x + boxWidth_2/2) &&
		(boxPos_1.x + boxWidth_1 / 2) >= (boxPos_2.x - boxWidth_2 / 2) &&
		(boxPos_1.y - boxHeight_1 / 2) <= (boxPos_2.y + boxHeight_2 / 2) &&
		(boxPos_1.y + boxHeight_1 / 2) >= (boxPos_2.y - boxHeight_2 / 2) &&
		(boxPos_1.z - boxDepth_1 / 2) <= (boxPos_2.z + boxDepth_2 / 2) &&
		(boxPos_1.z + boxDepth_1 / 2) >= (boxPos_2.z - boxDepth_2 / 2);
}

bool EngineManager::calculate_PointOnTriangle(glm::vec3& x, const glm::vec3& P, const glm::vec3& Q, const glm::vec3& R, const glm::vec3& position)
{
	glm::vec3 tempVector = x;
	tempVector.y -= 0.5;

	float A = calculate_Normal(Q - P, R - P);
	
	float U = calculate_Normal((Q + position) - tempVector, (R + position) - tempVector);
	float V = calculate_Normal((R + position) - tempVector, (P + position) - tempVector);
	float W = 1 - U - V;

	if (U >= 0 && V >= 0 && W >= 0)
	{
		float triangleHeight = U * (P.y) + V * (Q.y) + W * (R.y);
		x.y = (triangleHeight+position.y);
		return true;
	}
	else
	{
		return false;
	}
}

void EngineManager::switch_YZ(glm::vec3& vector)
{
	float tempValue = vector.z;
	vector.z = vector.y;
	vector.y = tempValue;
}

float EngineManager::calculate_Normal(const glm::vec3& AB, const glm::vec3& AC)
{
	return AB[0] * AC[2] - AC[0] * AB[2];
}

float EngineManager::calculate_Normal(const glm::vec3&& AB, const glm::vec3&& AC)
{
	return AB[0] * AC[2] - AC[0] * AB[2];
}
