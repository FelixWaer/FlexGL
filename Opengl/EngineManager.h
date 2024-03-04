#pragma once
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "FlexGL.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"


class EngineManager
{
public:
	std::vector<FXGL::Model*> ModelHandler;
	std::vector<FXGL::Line*> LineModelHandler;
	FXGL::Shader TheShader;
	Camera* TheCamera;
	GLFWwindow* TheWindow;

	int modelLoc;
	int viewLoc;
	int projLoc;

	void init_Window();
	void init_Engine();
	void tick_Engine();

private:
	FlexGL TheGame;

	float DeltaTime = 0.f;
	float LastFrame = 0.f;
};
