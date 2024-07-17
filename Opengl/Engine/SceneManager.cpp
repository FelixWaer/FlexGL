#include "SceneManager.h"

#include "glad/glad.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>

#include "EngineManager.h"
#include"../Rendering/Renderer.h"

const float SCR_WIDTH = 1920;
const float SCR_HEIGHT = 1080;

void SceneManager::begin_Scene()
{
	ActiveEngineCamera.init_GameObject();
	CubeObject.init_GameObject();

	TestLight.init_Light();
	TestLight.set_LightPosition(glm::vec3(0.f, 100.f, 0.f));
	TestLight.set_LightColor(glm::vec3(1.f));

	while (GameObjectsToBeAdded.empty() == false)
	{
		GameObject* addedGameObject = GameObjectsToBeAdded.front();
		GameObjectsToBeAdded.pop(),

		addedGameObject->game_Start();
		SceneGameObjects.emplace_back(addedGameObject);
	}
}


void SceneManager::tick_Scene(float deltaTime)
{
	check_Collision();
	tick_GameObjects(deltaTime);
	render_Models();
}

void SceneManager::set_SceneCamera(Camera* newSceneCamera)
{
	SceneCamera = newSceneCamera;
}

Camera* SceneManager::get_SceneCamera()
{
	return SceneCamera;
}

void SceneManager::add_GameObjectToScene(GameObject* gObject)
{
	GameObjectsToBeAdded.emplace(gObject);
}

void SceneManager::add_BoxColliderToScene(BoxCollision* boxCollider)
{
	SceneBoxColliders.emplace_back(boxCollider);
}

void SceneManager::add_SphereColliderToScene(SphereCollision* sphereCollider)
{
	SceneSphereColliders.emplace_back(sphereCollider);
}

void SceneManager::add_ModelToScene(Model* model)
{
	SceneModels.emplace_back(model);
}

void SceneManager::turnOff_DebugMode(bool turnOff)
{
	for (SphereCollision* sphere : SceneSphereColliders)
	{
		sphere->enable_SphereVisible(turnOff);
	}
	for (BoxCollision* sphere : SceneBoxColliders)
	{
		sphere->enable_BoxVisible(turnOff);
	}
}

void SceneManager::tick_GameObjects(float deltaTime)
{
	for (GameObject* gObject : SceneGameObjects)
	{
		gObject->tick(deltaTime);
	}
}

void SceneManager::check_Collision()
{
	if (SceneBoxColliders.size() > 1)
	{
		for (size_t i = 0; i < SceneBoxColliders.size(); i++)
		{
			for (size_t j = i + 1; j < SceneBoxColliders.size(); j++)
			{
				if (calculate_BoxCollision(SceneBoxColliders[i]->get_BoxPosition(), SceneBoxColliders[j]->get_BoxPosition(),
					SceneBoxColliders[i]->BoxHeight, SceneBoxColliders[i]->BoxWidth, SceneBoxColliders[i]->BoxDepth,
					SceneBoxColliders[j]->BoxHeight, SceneBoxColliders[j]->BoxWidth, SceneBoxColliders[j]->BoxDepth))
				{
					SceneBoxColliders[i]->call_CollisionEvent(SceneBoxColliders[j]);
					SceneBoxColliders[j]->call_CollisionEvent(SceneBoxColliders[i]);
				}
			}
		}
	}

	if (SceneSphereColliders.size() > 1)
	{
		for (size_t i = 0; i < SceneSphereColliders.size(); i++)
		{
			for (size_t j = i + 1; j < SceneSphereColliders.size(); j++)
			{
				if (calculate_SphereCollision(SceneSphereColliders[i]->get_SpherePosition(), SceneSphereColliders[j]->get_SpherePosition(),
					SceneSphereColliders[i]->get_SphereRadius(), SceneSphereColliders[j]->get_SphereRadius()))
				{
					SceneSphereColliders[i]->call_CollisionEvent(SceneSphereColliders[j]);
					SceneSphereColliders[j]->call_CollisionEvent(SceneSphereColliders[i]);
				}
			}
		}
	}
}

bool SceneManager::calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2)
{
	return (boxPos_1.x - boxWidth_1 / 2) <= (boxPos_2.x + boxWidth_2 / 2) &&
		(boxPos_1.x + boxWidth_1 / 2) >= (boxPos_2.x - boxWidth_2 / 2) &&
		(boxPos_1.y - boxHeight_1 / 2) <= (boxPos_2.y + boxHeight_2 / 2) &&
		(boxPos_1.y + boxHeight_1 / 2) >= (boxPos_2.y - boxHeight_2 / 2) &&
		(boxPos_1.z - boxDepth_1 / 2) <= (boxPos_2.z + boxDepth_2 / 2) &&
		(boxPos_1.z + boxDepth_1 / 2) >= (boxPos_2.z - boxDepth_2 / 2);
}

bool SceneManager::calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2)
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

void SceneManager::render_Models()
{
	glUseProgram(EngineManager::get()->get_Shader().ShaderProgram);
	EngineManager::get()->get_Shader().send_Vec3("CameraPos", get_SceneCamera()->get_CameraPosition());
	EngineManager::get()->get_Shader().send_Vec3("LightPos", TestLight.get_LightPosition());
	EngineManager::get()->get_Shader().send_Vec3("LightColor", TestLight.get_LightColor());
	for (auto model : SceneModels)
	{
		if (model->ModelMesh == nullptr || model->skybox == true)
		{
			continue;
		}
		glm::mat4 modelMatrix = glm::perspective(glm::radians(45.0f),
			EngineManager::get()->get_AspectRatio(), 0.1f, 400.f) * get_SceneCamera()->get_CameraView() * model->get_ModelMatrix();
		EngineManager::get()->get_Shader().send_Matrix("PositionMatrix", model->get_ModelMatrix());
		EngineManager::get()->get_Shader().send_Matrix("ModelMatrix", modelMatrix);
		EngineManager::get()->get_Shader().send_Bool("HasTexture", model->has_Texture());

		model->draw_Model();
	}
}