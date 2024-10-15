#pragma once

#include "../Rendering/RenderManager.h"
#include "SceneManager.h"
#include "WindowManager.h"

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

	float get_DeltaTime();
	int get_WindowWidth();
	int get_WindowHeight();
	float get_AspectRatio();
private:
	EngineManager() = default;

	inline static EngineManager* TheEngineManager = nullptr;

	SceneManager* ActiveScene = nullptr;
	WindowManager ActiveWindow;
	RenderManager RenderManager;

	float DeltaTime = 0.f;
	float LastFrame = 0.f;

	void tick_Engine();
};
