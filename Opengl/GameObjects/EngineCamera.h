#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Camera.h"
#include "../Engine/EventCallback.h"
#include "../GameObject Components/SphereCollision.h"
#include "../Components/Camera2D.h"

class BasicCube;
class Barrel;
class Grid;
class GameMap;
class Enemy;
class Entity;

class EngineCamera : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void set_GridMesh(GameMap* grid);

private:
	void input_WFunction();
	void input_AFunction();
	void input_SFunction();
	void input_DFunction();
	void input_OneFunction();
	void input_TwoFunction();
	void input_ThreeFunction();
	void input_LMouseFunction();
	void input_RMouseFunction();
	void input_ESCFunction();
	void collision_Function(GameObject* otherGameObject);

	void move_Player();
	GameMap* get_Chunk(glm::ivec2& chunkCord);

	Event* W_InputEvent = nullptr;
	Event* A_InputEvent = nullptr;
	Event* S_InputEvent = nullptr;
	Event* D_InputEvent = nullptr;
	Event* One_InputEvent = nullptr;
	Event* Two_InputEvent = nullptr;
	Event* Three_InputEvent = nullptr;
	Event* LM_InputEvent = nullptr;
	Event* RM_InputEvent = nullptr;
	Event* ESC_InputEvent = nullptr;
	Event* CollisionEvent = nullptr;

	Camera ActiveCamera;

	glm::ivec2 ChunkPosition = glm::ivec2(0.f);

	GameMap* activeChunk = nullptr;

	//std::unordered_map<glm::ivec2, GameMap*> Chunks;
	std::vector<GameMap*> Chunks;

	Entity* Placeable = nullptr;
	std::vector<Enemy*> Enemies;
	Enemy* Player = nullptr;
	glm::vec3 PlaceToMove = glm::vec3(0.f);

	bool IsPlacing = false;
	bool ControllerMode = false;
};

