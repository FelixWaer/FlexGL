#include "EngineCamera.h"

#include <iostream>

#include "../Engine/EngineManager.h"
#include "../Engine/Input.h"
#include "../GameObjects/BasicCube.h"

void EngineCamera::game_Start()
{
	//Set the Camera position
	ActiveCamera.update_CameraPosition(glm::vec3(0.f, 0.f, 5.f));

	//Set the Camera speed
	ActiveCamera.set_CameraSpeed(50.f);
	EngineManager::get()->get_ActiveScene()->set_SceneCamera(&ActiveCamera);

	//Initialize Camera by adding it to the Camera Handler.
	//TODO: Make Camera Handler do something
	//testCamera.init_Camera();

	W_InputEvent = make_Event(this, &EngineCamera::input_WFunction);
	A_InputEvent = make_Event(this, &EngineCamera::input_AFunction);
	S_InputEvent = make_Event(this, &EngineCamera::input_SFunction);
	D_InputEvent = make_Event(this, &EngineCamera::input_DFunction);
	LM_InputEvent = make_Event(this, &EngineCamera::input_LMouseFunction);
	RM_InputEvent = make_Event(this, &EngineCamera::input_RMouseFunction);
	ESC_InputEvent = make_Event(this, &EngineCamera::input_ESCFunction);
	CollisionEvent = make_Event(this, &EngineCamera::collision_Function);

	Input::bind_EventToKey(W_InputEvent, Key::W, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(A_InputEvent, Key::A, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(S_InputEvent, Key::S, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(D_InputEvent, Key::D, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(LM_InputEvent, Key::LMouse, KeyPress::OnPress);
	Input::bind_EventToKey(RM_InputEvent, Key::RMouse, KeyPress::OnPress);
	Input::bind_EventToKey(ESC_InputEvent, Key::ESCAPE, KeyPress::OnPress);
}

void EngineCamera::tick(float deltaTime)
{
	set_GameObjectPosition(ActiveCamera.get_CameraPosition());
}

void EngineCamera::set_GridMesh(Grid* grid)
{
	MapGrid = grid;
}

void EngineCamera::input_WFunction()
{
	ActiveCamera.move_CameraFront(true);
	ActiveCamera.move_2DCamera(glm::vec3(0.f, 1.f, 0.f));
}

void EngineCamera::input_AFunction()
{
	ActiveCamera.move_CameraSide(false);
	ActiveCamera.move_2DCamera(glm::vec3(1.f, 0.f, 0.f));
}

void EngineCamera::input_SFunction()
{
	ActiveCamera.move_CameraFront(false);
	ActiveCamera.move_2DCamera(glm::vec3(0.f, -1.f, 0.f));
}

void EngineCamera::input_DFunction()
{
	ActiveCamera.move_CameraSide(true);
	ActiveCamera.move_2DCamera(glm::vec3(-1.f, 0.f, 0.f));
}

void EngineCamera::input_LMouseFunction()
{
	BasicCube* newCube = new BasicCube;
	newCube->init_GameObject();
	glm::vec3 tempPos = glm::vec3(EngineManager::get()->get_ActiveWindow().get_MousePositionX(),
		EngineManager::get()->get_ActiveWindow().get_MousePositionY(), 0.f);
	tempPos -= ActiveCamera.get_2DCameraPosition();
	newCube->set_GameObjectPosition(tempPos);

	Cubes.emplace_back(newCube);
	std::cout << "Mouse pressed" << std::endl;
	std::cout << "new XPos: " << tempPos.x << " new YPos: " << tempPos.y << std::endl;
}

void EngineCamera::input_RMouseFunction()
{
	double xPos = EngineManager::get()->get_ActiveWindow().get_MousePositionX();
	double yPos = EngineManager::get()->get_ActiveWindow().get_MousePositionY();
	xPos -= ActiveCamera.get_2DCameraPosition().x;
	yPos -= ActiveCamera.get_2DCameraPosition().y;

	glm::ivec2 gridCord = glm::ivec2(xPos, yPos);

	gridCord.x = gridCord.x >> 6;
	gridCord.y = gridCord.y >> 6;
	//gridCord.x -= 1;
	gridCord.y += 1;

	std::cout << gridCord.x << " " << gridCord.y << std::endl;

	MapGrid->test(gridCord);
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
