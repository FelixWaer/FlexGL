#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include "SceneManager.h"
#include "WindowManager.h"
#include "Input.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Shader.h"
#include "../GameObjects/EngineCamera.h"

class EngineManager
{
public:
	EngineManager(EngineManager& other) = delete;
	~EngineManager();

	static EngineManager* get();

	void init_Engine();
	void run_Engine();

	void set_ActiveScene(SceneManager* newActiveScene);
	SceneManager* get_ActiveScene();
	WindowManager& get_ActiveWindow();
	Shader& get_Shader();

	float get_DeltaTime();
	int get_WindowWidth();
	int get_WindowHeight();
	float get_AspectRatio();
private:
	EngineManager() = default;

	inline static EngineManager* TheEngineManager = nullptr;

	SceneManager* ActiveScene = nullptr;
	WindowManager ActiveWindow;
	Shader TheShader;

	float DeltaTime = 0.f;
	float LastFrame = 0.f;

	void tick_Engine();
};
