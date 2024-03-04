#pragma once

#include "Model.h"
#include "Camera.h"

class EngineManager;
struct GLFWwindow;

class FlexGL
{
public:
	void game_Start(EngineManager* EM);
	void tick(EngineManager* EM, float deltaTime);
	void Input(GLFWwindow* window);
private:

	FXGL::Line line1 = FXGL::Line(true);
	FXGL::Line line2 = FXGL::Line(true);
	FXGL::Line line3 = FXGL::Line(false);
	FXGL::Model Cube;

	Camera Camera_1;
};

