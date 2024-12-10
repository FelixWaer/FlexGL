#pragma once

#include "../Rendering/RenderManager.h"
#include "SceneManager.h"
#include "WindowManager.h"
#include "SystemManager.h"
#include "LuaManager.h"

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
	RenderManager& get_RenderManager();
	LuaManager& get_LuaManager();

	float get_DeltaTime();
	int get_WindowWidth();
	int get_WindowHeight();
	float get_AspectRatio();
	glm::vec2 get_MousePosition();
	void set_MousePosCenter();
private:
	EngineManager() = default;

	inline static EngineManager* TheEngineManager = nullptr;

	SceneManager* ActiveScene = nullptr;
	WindowManager ActiveWindow;
	RenderManager RenderManager;
	SystemManager SystemManagerTest;
	LuaManager LuaManager;

	float DeltaTime = 0.f;
	float LastFrame = 0.f;
	float FrameTimer = 0.f;
	int FPSCounter = 0;

	void tick_Engine();
};
