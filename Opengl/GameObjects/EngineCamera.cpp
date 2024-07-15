#include "EngineCamera.h"

#include "../Engine/EngineManager.h"
#include "../Engine/Input.h"

void EngineCamera::game_Start()
{
	//Set the Camera position
	ActiveCamera.update_CameraPosition(glm::vec3(0.f));

	//Set the Camera speed
	ActiveCamera.set_CameraSpeed(50.f);
	EngineManager::get()->get_ActiveScene()->set_SceneCamera(&ActiveCamera);

	//Initialize Camera by adding it to the Camera Handler.
	//Camera Handler does nothing right now
	//testCamera.init_Camera();
}

void EngineCamera::tick(float deltaTime)
{
	if (Input::key_HeldDown(GLFW_KEY_W))
	{
		ActiveCamera.move_CameraFront(true);
	}
	if (Input::key_HeldDown(GLFW_KEY_A))
	{
		ActiveCamera.move_CameraSide(false);
	}
	if (Input::key_HeldDown(GLFW_KEY_S))
	{
		ActiveCamera.move_CameraFront(false);
	}
	if (Input::key_HeldDown(GLFW_KEY_D))
	{
		ActiveCamera.move_CameraSide(true);
	}

	if (Input::key_Pressed(GLFW_KEY_ESCAPE))
	{
		EngineManager::get()->get_ActiveWindow().close_Window();
	}
}
