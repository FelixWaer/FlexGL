#include "EngineCamera.h"

#include <iostream>

#include "../Engine/EngineManager.h"
#include "../Engine/Input.h"
#include "Barrel.h"
#include "Enemy.h"
#include "GameMap.h"
#include "../Components/CollisionComponent.h"
#include "../Components/DamageComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"

void EngineCamera::game_Start()
{
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			GameMap* tempMap = new GameMap;
			tempMap->create_Enity();
			tempMap->set_ChunkCord(glm::ivec2(x, y));
			Chunks.emplace_back(tempMap);
		}
	}

	//GridMap = new GameMap;
	//GridMap->create_Enity();
	//GridMap2 = new GameMap;
	//GridMap2->create_Enity();
	//GridMap->set_ChunkCord(glm::ivec2(0, 0));
	//GridMap2->set_ChunkCord(glm::ivec2(0, 2));
	//GridMap = Chunks[4];

	Player = new Enemy;
	Player->create_Enity();
	Player->get_Component<PositionComponent>().Position += glm::vec3(400.f, 400.f, 0.f);
	Player->get_Component<MovementComponent>().Speed = 150.f;
	Player->get_Component<SpriteComponent>().MaterialName = "PlayerMaterial";
	Player->get_Component<CollisionComponent>().Radius = 256.f;
	Player->get_Component<HealthComponent>().Health = 100.f;
	Player->get_Component<TagComponent>().Tag = "Player";
	Player->get_Component<DamageComponent>().Damage = 100.f;

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
	Two_InputEvent = make_Event(this, &EngineCamera::input_TwoFunction);
	Three_InputEvent = make_Event(this, &EngineCamera::input_ThreeFunction);
	LM_InputEvent = make_Event(this, &EngineCamera::input_LMouseFunction);
	RM_InputEvent = make_Event(this, &EngineCamera::input_RMouseFunction);
	ESC_InputEvent = make_Event(this, &EngineCamera::input_ESCFunction);
	CollisionEvent = make_Event(this, &EngineCamera::collision_Function);

	Input::bind_EventToKey(W_InputEvent, Key::W, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(A_InputEvent, Key::A, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(S_InputEvent, Key::S, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(D_InputEvent, Key::D, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(One_InputEvent, Key::One, KeyPress::OnPress);
	Input::bind_EventToKey(Two_InputEvent, Key::Two, KeyPress::OnPress);
	Input::bind_EventToKey(Three_InputEvent, Key::Three, KeyPress::OnPress);
	Input::bind_EventToKey(LM_InputEvent, Key::LMouse, KeyPress::OnPress);
	Input::bind_EventToKey(RM_InputEvent, Key::RMouse, KeyPress::OnPress);
	Input::bind_EventToKey(ESC_InputEvent, Key::ESCAPE, KeyPress::OnPress);

	glm::vec3 tempPos = glm::vec3(EngineManager::get()->get_ActiveWindow().get_MousePositionX(),
		EngineManager::get()->get_ActiveWindow().get_MousePositionY(), 0.f);
	tempPos -= ActiveCamera.get_2DCameraPosition();

	glm::ivec2 newChunkPos(tempPos.x, tempPos.y);
	newChunkPos.x >>= 11;
	newChunkPos.y >>= 11;

	ChunkPosition = newChunkPos;
	std::cout << "xpos: " << ChunkPosition.x << "ypos: " << ChunkPosition.y << std::endl;

	for (GameMap* chunk : Chunks)
	{
		if (chunk->get_ChunkCord() == ChunkPosition)
		{
			activeChunk = chunk;
			break;
		}
	}
}

void EngineCamera::tick(float deltaTime)
{
	set_GameObjectPosition(ActiveCamera.get_CameraPosition());

	glm::vec3 newLifeColor(1.f);
	newLifeColor *= (Player->get_Component<HealthComponent>().Health / 100.f);
	EngineManager::get()->get_RenderManager().get_Material("PlayerMaterial").ColorHue = newLifeColor;

	if (glm::distance(Player->get_Component<PositionComponent>().Position, PlaceToMove) < 10.f)
	{
		Player->get_Component<MovementComponent>().Direction = glm::vec3(0.f);
	}

	for (Enemy* enemy : Enemies)
	{
		if (glm::distance(Player->get_Component<PositionComponent>().Position, enemy->get_Component<PositionComponent>().Position) < 10.f)
		{
			continue;
		}
		glm::vec3 tempVec = glm::normalize(Player->get_Component<PositionComponent>().Position - enemy->get_Component<PositionComponent>().Position);
		tempVec.z = 0.f;

		enemy->get_Component<MovementComponent>().Direction = tempVec;
	}

	glm::vec3 tempPos = glm::vec3(EngineManager::get()->get_ActiveWindow().get_MousePositionX(),
		EngineManager::get()->get_ActiveWindow().get_MousePositionY(), 0.f);
	tempPos -= ActiveCamera.get_2DCameraPosition();

	glm::ivec2 newChunkPos(tempPos.x, tempPos.y);
	newChunkPos.y += 64;
	newChunkPos.x >>= 11;
	newChunkPos.y >>= 11;

	if (newChunkPos != ChunkPosition)
	{
		ChunkPosition = newChunkPos;
		//std::cout << "xpos: " << ChunkPosition.x << "ypos: " << ChunkPosition.y << std::endl;

		for (GameMap* chunk : Chunks)
		{
			if (chunk->get_ChunkCord() == ChunkPosition)
			{
				activeChunk = chunk;
				break;
			}
		}
	}

	if (IsPlacing == true && Placeable != nullptr)
	{
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

		gridCord -= ChunkPosition * 32;

		Placeable->get_Component<PositionComponent>().Position = glm::vec3(x, y, 0.0f);

		if (activeChunk->check_IfTileTaken(gridCord) == true)
		{
			EngineManager::get()->get_RenderManager().get_Material("PlacementMaterial").ColorHue = glm::vec3(1.f, 0.f, 0.f);
		}
		else
		{
			EngineManager::get()->get_RenderManager().get_Material("PlacementMaterial").ColorHue = glm::vec3(0.f, 1.f, 0.f);
		}
	}
}

void EngineCamera::set_GridMesh(GameMap* grid)
{
	//GridMap = grid;
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
	if (IsPlacing == false && ControllerMode == false)
	{
		Placeable = new Barrel;
		Placeable->create_Enity();

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

		Placeable->get_Component<PositionComponent>().Position = glm::vec3(x, y, 0.0f);
		Placeable->get_Component<SpriteComponent>().MaterialName = "PlacementMaterial";

		IsPlacing = true;
	}
	else
	{
		//delete PlaceCube;
		//PlaceCube = nullptr;
		//IsPlacing = false;
	}
}

void EngineCamera::input_TwoFunction()
{
	if (IsPlacing == false && ControllerMode == false)
	{
		Placeable = new Enemy;
		Placeable->create_Enity();

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

		Placeable->get_Component<PositionComponent>().Position = glm::vec3(x, y, 0.0f);
		Placeable->get_Component<SpriteComponent>().MaterialName = "EnemyMaterial";

		IsPlacing = true;
	}
	else
	{
		//delete PlaceCube;
		//PlaceCube = nullptr;
		//IsPlacing = false;
	}
}

void EngineCamera::input_ThreeFunction()
{
	if (IsPlacing == false && ControllerMode == false)
	{
		ControllerMode = true;
	}
	else
	{
		ControllerMode = false;
	}
}

void EngineCamera::input_LMouseFunction()
{
	if (ControllerMode == true)
	{
		move_Player();
		return;
	}

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

	gridCord -= ChunkPosition * 32;

	if (activeChunk->check_IfTileTaken(gridCord) == false && Placeable != nullptr)
	{
		Placeable->get_Component<PositionComponent>().Position = glm::vec3(x, y, 0.0f);
		if (Placeable->get_Component<SpriteComponent>().MaterialName == "PlacementMaterial")
		{
			Placeable->get_Component<SpriteComponent>().MaterialName = "ObjectMaterial";
		}

		if (Placeable->get_Component<TagComponent>().Tag == "Enemy")
		{
			Enemies.emplace_back(static_cast<Enemy*>(Placeable));
		}

		Placeable = nullptr;

		IsPlacing = false;

		activeChunk->set_TileAsTaken(gridCord);
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

	glm::ivec2 neighborTileCord = gridCord;

	gridCord -= ChunkPosition * 32;

	if (activeChunk->check_IfTileTaken(gridCord) == false)
	{
		glm::ivec2 neighborChunkCord = ChunkPosition;
		if (gridCord.x == 0)
		{
			neighborChunkCord.x -= 1;
			neighborTileCord.x -= 1;
			activeChunk->change_TileEdges(gridCord, neighborTileCord, get_Chunk(neighborChunkCord));
		}
		else if(gridCord.x == 32)
		{
			neighborChunkCord.x += 1;
			neighborTileCord.x += 1;
			activeChunk->change_TileEdges(gridCord, neighborTileCord, get_Chunk(neighborChunkCord));
		}
		else if (gridCord.y == 0)
		{
			neighborChunkCord.y -= 1;
			neighborTileCord.y -= 1;
			activeChunk->change_TileEdges(gridCord, neighborTileCord, get_Chunk(neighborChunkCord));
		}
		else if (gridCord.y == 32)
		{
			neighborChunkCord.y += 1;
			neighborTileCord.y += 1;
			activeChunk->change_TileEdges(gridCord, neighborTileCord, get_Chunk(neighborChunkCord));
		}
		else
		{
			activeChunk->change_Tile(gridCord);
		}
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

void EngineCamera::move_Player()
{
	glm::vec3 tempPos = glm::vec3(EngineManager::get()->get_ActiveWindow().get_MousePositionX(),
	EngineManager::get()->get_ActiveWindow().get_MousePositionY(), 0.f);
	tempPos -= ActiveCamera.get_2DCameraPosition();

	glm::vec3 tempPlayerVec = glm::normalize(tempPos - Player->get_Component<PositionComponent>().Position);

	Player->get_Component<MovementComponent>().Direction = tempPlayerVec;
	PlaceToMove = tempPos;
}

GameMap* EngineCamera::get_Chunk(glm::ivec2& chunkCord)
{
	for (GameMap* chunk : Chunks)
	{
		if (chunk->get_ChunkCord() == chunkCord)
		{
			return chunk;
		}
	}

	return nullptr;
}
