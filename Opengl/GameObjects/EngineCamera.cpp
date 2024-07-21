#include "EngineCamera.h"

#include <iostream>

#include "../Engine/EngineManager.h"
#include "../Engine/Input.h"

void EngineCamera::game_Start()
{
	//Set the Camera position
	ActiveCamera.update_CameraPosition(glm::vec3(0.f, 0.f, 5.f));

	//Set the Camera speed
	ActiveCamera.set_CameraSpeed(50.f);
	EngineManager::get()->get_ActiveScene()->set_SceneCamera(&ActiveCamera);

	//Initialize Camera by adding it to the Camera Handler.
	//Camera Handler does nothing right now
	//testCamera.init_Camera();

	//InputEvent = new EventCallback(this, &EngineCamera::test_Function);
	W_InputEvent = make_Event(this, &EngineCamera::input_WFunction);
	A_InputEvent = make_Event(this, &EngineCamera::input_AFunction);
	S_InputEvent = make_Event(this, &EngineCamera::input_SFunction);
	D_InputEvent = make_Event(this, &EngineCamera::input_DFunction);
	LM_InputEvent = make_Event(this, &EngineCamera::input_LMouseFunction);
	ESC_InputEvent = make_Event(this, &EngineCamera::input_ESCFunction);
	CollisionEvent = make_Event(this, &EngineCamera::collision_Function);

	Input::bind_EventToKey(W_InputEvent, Key::W, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(A_InputEvent, Key::A, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(S_InputEvent, Key::S, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(D_InputEvent, Key::D, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(LM_InputEvent, Key::LMouse, KeyPress::OnPress);
	Input::bind_EventToKey(ESC_InputEvent, Key::ESCAPE, KeyPress::OnPress);
}

void EngineCamera::tick(float deltaTime)
{
	set_GameObjectPosition(ActiveCamera.get_CameraPosition());
}

void EngineCamera::input_WFunction()
{
	ActiveCamera.move_CameraFront(true);
}

void EngineCamera::input_AFunction()
{
	ActiveCamera.move_CameraSide(false);
}

void EngineCamera::input_SFunction()
{
	ActiveCamera.move_CameraFront(false);
}

void EngineCamera::input_DFunction()
{
	ActiveCamera.move_CameraSide(true);
}

void EngineCamera::input_LMouseFunction()
{
	std::cout << "Mouse pressed" << std::endl;
}

void EngineCamera::input_ESCFunction()
{
	EngineManager::get()->get_ActiveWindow().close_Window();
}

void EngineCamera::collision_Function(GameObject* otherGameObject)
{
	if (otherGameObject == nullptr)
	{
		return;
	}

	if (otherGameObject->has_Tag("BasicCube") == true)
	{
		std::cout << "BasicCube" << std::endl;
	}
}
