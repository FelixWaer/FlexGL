#include "EngineManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Input.h"

EngineManager::~EngineManager()
{
	glfwTerminate();
	std::cout << "Engine Closed" << std::endl;
	delete TheEngineManager;
}

EngineManager* EngineManager::get()
{
	if (TheEngineManager == nullptr)
	{
		TheEngineManager = new EngineManager;
	}
	return TheEngineManager;
}

void EngineManager::init_Engine()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	ActiveWindow.init_Window();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);


	RenderManager.init_RenderManager();

	SceneManager* basicScene = new SceneManager;
	set_ActiveScene(basicScene);
}

void EngineManager::run_Engine()
{
	while (!glfwWindowShouldClose(ActiveWindow.get_Window()))
	{
		tick_Engine();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(ActiveWindow.get_Window());
		glfwPollEvents();
	}
}

void EngineManager::set_ActiveScene(SceneManager* newActiveScene)
{
	ActiveScene = newActiveScene;
	ActiveScene->begin_Scene();
}

SceneManager* EngineManager::get_ActiveScene()
{
	return ActiveScene;
}

WindowManager& EngineManager::get_ActiveWindow()
{
	return ActiveWindow;
}

float EngineManager::get_DeltaTime()
{
	return DeltaTime;
}

int EngineManager::get_WindowWidth()
{
	return ActiveWindow.get_WindowWidth();
}

int EngineManager::get_WindowHeight()
{
	return ActiveWindow.get_WindowHeight();
}

float EngineManager::get_AspectRatio()
{
	return ActiveWindow.get_AspectRatio();
}

void EngineManager::tick_Engine()
{
	/*----Start of Temporary Code----*/
	//Calculating DeltaTime
	float currentFrame = static_cast<float>(glfwGetTime());
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;
	//std::cout << 1 / DeltaTime << std::endl;

	glClearColor(0.f, 0.8f, 1.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(10);
	glPointSize(5);

	/*-----End of Temporary Code-----*/
	Input::call_KeyEvents();

	ActiveScene->tick_Scene(DeltaTime);

	RenderManager.render_Scene(ActiveScene);

	Input::reset_Input();
}