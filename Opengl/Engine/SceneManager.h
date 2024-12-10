#pragma once
#include <queue>
#include <vector>

#include "ComponentManager.h"
#include "EntityManager.h"
#include "../Rendering/Model.h"
#include "../Rendering/Light.h"

class SceneManager
{
public:
	SceneManager() = default;

	void begin_Scene();
	void tick_Scene(float deltaTime);

	ComponentManager& get_ComponentManager();
	EntityManager& get_EntityManager();
	
	void set_ActiveCamera(Entity* newActiveCamera);
	Entity* get_ActiveCamera();

	std::vector<Light*>& get_SceneLights();

	void add_LightToScene(Light* light);


private:
	Light TestLight;

	std::vector<Light*> SceneLights;

	ComponentManager SceneComponentManager;
	EntityManager SceneEntityManager;
	Entity* ActiveCamera = nullptr;

	bool calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2);
	bool calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2);
};

