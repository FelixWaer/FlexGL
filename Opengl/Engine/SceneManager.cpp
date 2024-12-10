#include "SceneManager.h"

#include "glad/glad.h"

#include "glm/glm.hpp"
#include <glm/ext/matrix_clip_space.hpp>

#include "../Components/CameraComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/ScriptComponent.h"
#include "../FlexLibrary/FlexTimer/Flextimer.h"
#include "../GameObjects/Cube.h"
#include "../GameObjects/SceneCamera.h"
#include "../GameObjects/Floor.h"

void SceneManager::begin_Scene()
{
	Entity* camera = new SceneCamera;
	camera->create_Entity();
	EngineManager::get()->get_RenderManager().ActiveCamera = camera;

	Entity* World = new Entity;
	World->create_Entity();

	Cube* cube = new Cube;
	cube->create_Entity();

	Floor* floor = new Floor;
	floor->create_Entity();

	EngineManager::get()->get_LuaManager().run_Script("Scripts/SceneStart.Lua", World->get_EntityID());

	TestLight.init_Light();
	TestLight.set_LightPosition(glm::vec3(0.f, 10.f, 0.f));
	TestLight.set_LightColor(glm::vec3(1.f));
}

void SceneManager::tick_Scene(float deltaTime)
{
	SceneEntityManager.tick_Entities(deltaTime);
}

ComponentManager& SceneManager::get_ComponentManager()
{
	return SceneComponentManager;
}

EntityManager& SceneManager::get_EntityManager()
{
	return SceneEntityManager;
}

void SceneManager::set_ActiveCamera(Entity* newActiveCamera)
{
	if (newActiveCamera->has_Component<CameraComponent>() == true)
	{
		ActiveCamera = newActiveCamera;
	}
}

Entity* SceneManager::get_ActiveCamera()
{
	return ActiveCamera;
}


std::vector<Light*>& SceneManager::get_SceneLights()
{
	return SceneLights;
}

void SceneManager::add_LightToScene(Light* light)
{
	SceneLights.emplace_back(light);
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
