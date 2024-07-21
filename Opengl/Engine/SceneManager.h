#pragma once
#include <queue>
#include <vector>

#include "GameObject.h"
#include "../GameObject Components/BoxCollision.h"
#include "../GameObject Components/SphereCollision.h"
#include "../GameObjects/EngineCamera.h"
#include "../GameObjects/BasicCube.h"
#include "../Rendering/Model.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Light.h"

class SceneManager
{
public:
	SceneManager() = default;

	void begin_Scene();
	void tick_Scene(float deltaTime);

	void set_SceneCamera(Camera* newSceneCamera);
	Camera* get_SceneCamera();
	std::vector<Model*>& get_SceneModels();
	std::vector<Light*>& get_SceneLights();

	void add_GameObjectToScene(GameObject* gObject);
	void add_BoxColliderToScene(BoxCollision* boxCollider);
	void add_SphereColliderToScene(SphereCollision* sphereCollider);
	void add_ModelToScene(Model* model);
	void add_LightToScene(Light* light);

	void turnOff_DebugMode(bool turnOff);
private:
	//Start of Temporary Code
	Light TestLight;
	EngineCamera ActiveEngineCamera;
	BasicCube CubeObject;
	BasicCube CubeObject2;
	//End of Temporary Code
	Camera* SceneCamera = nullptr;

	std::vector<GameObject*> SceneGameObjects;
	std::queue<GameObject*> GameObjectsToBeAdded;

	std::vector<BoxCollision*> SceneBoxColliders;
	std::vector<SphereCollision*> SceneSphereColliders;

	std::vector<Model*> SceneModels;
	std::vector<Light*> SceneLights;

	void tick_GameObjects(float deltaTime);

	void check_Collision();
	bool calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2);
	bool calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2);
};

