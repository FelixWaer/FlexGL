#pragma once
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "FlexGL.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Model.h"
#include "../Rendering/Camera.h"
#include "../Rendering/Light.h"
#include "GameObject.h"
#include "../GameObject Components/SphereCollision.h"
#include "../GameObject Components/BoxCollision.h"

class EngineManager
{
public:
	static EngineManager* get_Engine();

	FXGL::Shader TheShader;
	FXGL::Shader SkyboxShader;

	Camera* ActiveCamera;
	GLFWwindow* TheWindow;

	FlexClient flexClient;

	Model* TheTerrain = nullptr;
	glm::vec3* CharacterPoint = nullptr;

	bool Scene_2 = false;
	int Seed = 64363626;
	float TerrainHeight = 200.f;
	float GreedSize = 400.f;

	void init_Window();
	void init_Engine();
	void tick_Engine();

	void check_Collision();
	void add_ToModelHandler(Model* modelPtr);
	void add_ToGameObjectHandler(GameObject* gameObjectPtr);
	void add_ToSphereCollisionHandler(SphereCollision* sphereCollisionPtr);
	void add_ToBoxCollisionHandler(BoxCollision* boxCollisionPtr);
	float get_DeltaTime();

	void add_ToCameraHandler(Camera* CameraPtr);
	void set_ActiveCamera(Camera* cameraPtr);
	Camera& get_ActiveCamera();
	void set_Skybox(Model* skyboxModel);
	Model* get_Skybox();

	void turnOff_DebugMode(bool turnOff);
	static bool calculate_PointOnTriangle(glm::vec3& x, const glm::vec3& P, const glm::vec3& Q, const glm::vec3& R, const glm::vec3& position);
private:
	inline static EngineManager* TheEngineManager = nullptr;

	FlexGL TheGame;
	Light TheLight;
	Model* TheSkybox = nullptr;

	std::vector<Model*> ModelHandler;
	std::vector<GameObject*> GameObjectHandler;
	std::vector<GameObject*> GameObjectsToBeAdded;
	std::vector<SphereCollision*> SphereCollisionHandler;
	std::vector<BoxCollision*> BoxCollisionHandler;
	std::vector<Camera*> CameraHandler;

	float DeltaTime = 0.f;
	float LastFrame = 0.f;

	bool calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2);
	bool calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2);
	static void switch_YZ(glm::vec3& vector);

	static float calculate_Normal(const glm::vec3& AB, const glm::vec3& AC);
	static float calculate_Normal(const glm::vec3&& AB, const glm::vec3&& AC);
};
