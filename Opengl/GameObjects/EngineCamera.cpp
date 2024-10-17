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
	One_InputEvent = make_Event(this, &EngineCamera::input_OneFunction);
	LM_InputEvent = make_Event(this, &EngineCamera::input_LMouseFunction);
	RM_InputEvent = make_Event(this, &EngineCamera::input_RMouseFunction);
	ESC_InputEvent = make_Event(this, &EngineCamera::input_ESCFunction);
	CollisionEvent = make_Event(this, &EngineCamera::collision_Function);

	Input::bind_EventToKey(W_InputEvent, Key::W, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(A_InputEvent, Key::A, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(S_InputEvent, Key::S, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(D_InputEvent, Key::D, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(One_InputEvent, Key::One, KeyPress::OnPress);
	Input::bind_EventToKey(LM_InputEvent, Key::LMouse, KeyPress::OnPress);
	Input::bind_EventToKey(RM_InputEvent, Key::RMouse, KeyPress::OnPress);
	Input::bind_EventToKey(ESC_InputEvent, Key::ESCAPE, KeyPress::OnPress);
}

void EngineCamera::tick(float deltaTime)
{
	set_GameObjectPosition(ActiveCamera.get_CameraPosition());

	if (IsPlacing == true && PlaceCube != nullptr)
	{
		glm::vec3 tempPos = glm::vec3(EngineManager::get()->get_ActiveWindow().get_MousePositionX(),
			EngineManager::get()->get_ActiveWindow().get_MousePositionY(), 0.f);
		tempPos -= ActiveCamera.get_2DCameraPosition();

		glm::ivec2 gridCord;

		int x = tempPos.x;
		x = x >> 6;
		gridCord.x = x;
		x = x << 6;
		x += 32;
		int y = tempPos.y;
		y = y >> 6;
		gridCord.y = y;
		y = y << 6;
		y += 32;

		gridCord.y += 1;

		PlaceCube->update_Position(glm::vec3(x, y, 0.0f));

		if (MapGrid->check_IfTileTaken(gridCord) == true)
		{
			EngineManager::get()->get_RenderManager().get_Material("PlacementMaterial").ColorHue = glm::vec3(1.f, 0.f, 0.f);
		}
		else
		{
			EngineManager::get()->get_RenderManager().get_Material("PlacementMaterial").ColorHue = glm::vec3(0.f, 1.f, 0.f);
		}
	}
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

void EngineCamera::input_OneFunction()
{
	if (IsPlacing == false)
	{
		PlaceCube = new BasicCube;
		PlaceCube->init_GameObject();
		PlaceCube->init_Entity();

		glm::vec3 tempPos = glm::vec3(EngineManager::get()->get_ActiveWindow().get_MousePositionX(),
			EngineManager::get()->get_ActiveWindow().get_MousePositionY(), 0.f);
		tempPos -= ActiveCamera.get_2DCameraPosition();

		int x = tempPos.x;
		x = x >> 6;
		x = x << 6;
		x += 32;
		int y = tempPos.y;
		y = y >> 6;
		y = y << 6;
		y += 32;

		PlaceCube->set_GameObjectPosition(glm::vec3(x, y, 0.0f));
		PlaceCube->update_Position(glm::vec3(x, y, 0.0f));
		PlaceCube->set_Material("PlacementMaterial");
		IsPlacing = true;
	}
	else
	{
		//delete PlaceCube;
		//PlaceCube = nullptr;
		//IsPlacing = false;
	}
}

void EngineCamera::input_LMouseFunction()
{
	glm::vec3 tempPos = glm::vec3(EngineManager::get()->get_ActiveWindow().get_MousePositionX(),
		EngineManager::get()->get_ActiveWindow().get_MousePositionY(), 0.f);
	tempPos -= ActiveCamera.get_2DCameraPosition();

	glm::ivec2 gridCord;

	int x = tempPos.x;
	x = x >> 6;
	gridCord.x = x;
	x = x << 6;
	x += 32;
	int y = tempPos.y;
	y = y >> 6;
	gridCord.y = y;
	y = y << 6;
	y += 32;

	gridCord.y += 1;


	if (MapGrid->check_IfTileTaken(gridCord) == false)
	{
		BasicCube* newCube = new BasicCube;
		newCube->init_GameObject();
		newCube->init_Entity();

		newCube->update_Position(glm::vec3(x, y, 0.0f));
		newCube->set_Material("ObjectMaterial");

		Cubes.emplace_back(newCube);

		std::cout << "Mouse pressed" << std::endl;
		std::cout << "new XPos: " << tempPos.x << " new YPos: " << tempPos.y << std::endl;

		MapGrid->set_TileAsTaken(gridCord);
	}
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
	gridCord.y += 1;

	if (MapGrid->check_IfTileTaken(gridCord) == false)
	{
		MapGrid->test(gridCord);
	}
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
