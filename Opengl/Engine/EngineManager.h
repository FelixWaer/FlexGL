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
	inline static EngineManager* TheEngineManager = nullptr;
	static EngineManager* create_EngineManager();

	FXGL::Shader TheShader;
	Camera* ActiveCamera;
	GLFWwindow* TheWindow;

	Model* TheTerrain = nullptr;
	glm::vec3* CharacterPoint = nullptr;

	int ModelLoc;
	int PositionLoc;
	int CameraPosLoc;
	int lightPosLoc;
	int lightColorLoc;

	bool Scene_2 = false;
	int Seed = 4576782387;
	float TerrainHeight = 100.f;

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

	void turnOff_DebugMode(bool turnOff);
	static bool calculate_PointOnTriangle(glm::vec3& x, const glm::vec3& P, const glm::vec3& Q, const glm::vec3& R, const glm::vec3& position);
private:
	FlexGL TheGame;

	//glm::vec3 LightPosition = glm::vec3(0.f);
	Light TheLight;

	std::vector<Model*> ModelHandler;
	std::vector<GameObject*> GameObjectHandler;
	std::vector<SphereCollision*> SphereCollisionHandler;
	std::vector<BoxCollision*> BoxCollisionHandler;
	std::vector<Camera*> CameraHandler;

	float DeltaTime = 0.f;
	float LastFrame = 0.f;

	bool calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2);
	bool calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2);
	static void switch_YZ(glm::vec3& vector);

	float Degrees = 0.f;
	float DegreesColor = 0.f;
	float Radius = 15.f;
	float SmallerBigger = 1.f;
	float SmallerBiggerColor = 1.f;
	void move_Light(float deltaTime);
	static float calculate_Normal(const glm::vec3& AB, const glm::vec3& AC);
	static float calculate_Normal(const glm::vec3&& AB, const glm::vec3&& AC);
};
