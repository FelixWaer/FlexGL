#pragma once
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "FlexGL.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "GameObject.h"
#include "GameObject Components/SphereCollision.h"
#include "GameObject Components/BoxCollision.h"

class EngineManager
{
public:
	inline static EngineManager* TheEngineManager = nullptr;
	static EngineManager* create_EngineManager();

	FXGL::Shader TheShader;
	Camera* TheCamera;
	GLFWwindow* TheWindow;

	int modelLoc;
	int viewLoc;
	int projLoc;

	void init_Window();
	void init_Engine();
	void tick_Engine();

	void check_Collision();
	void add_ToModelHandler(Model* modelPtr);
	void add_ToLineModelHandler(Line* lineModelPtr);
	void add_ToGameObjectHandler(GameObject* gameObjectPtr);
	void add_ToSphereCollisionHandler(SphereCollision* sphereCollisionPtr);
	void add_ToBoxCollisionHandler(BoxCollision* boxCollisionPtr);
private:
	FlexGL TheGame;

	std::vector<Model*> ModelHandler;
	std::vector<Line*> LineModelHandler;
	std::vector<GameObject*> GameObjectHandler;
	std::vector<SphereCollision*> SphereCollisionHandler;
	std::vector<BoxCollision*> BoxCollisionHandler;

	float DeltaTime = 0.f;
	float LastFrame = 0.f;

	bool calculate_SphereCollision(glm::vec3 spherePos_1, glm::vec3 spherePos_2, float sphereRadius_1, float sphereRadius_2);
	bool calculate_BoxCollision(glm::vec3 boxPos_1, glm::vec3 boxPos_2, float boxHeight_1, float boxWidth_1, float boxDepth_1, float boxHeight_2, float boxWidth_2, float boxDepth_2);
};
