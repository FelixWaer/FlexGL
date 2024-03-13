#pragma once

#include "Camera.h"
#include "GameObjects/Door.h"
#include "GameObjects/PickUpItem.h"
#include "GameObjects/Player.h"
#include "GameObjects/Graphs.h"
#include "GameObjects/NPC.h"
#include "GameObjects/Box.h"
	
class EngineManager;
struct GLFWwindow;

class FlexGL
{
public:
	void game_Start(EngineManager* EM);
	void tick(EngineManager* EM, float deltaTime);
	void Input(GLFWwindow* window);
private:

	Graphs graph_1;

	std::vector<Camera*> camera;
	int CameraIndex = 0;
	Camera Camera_1;
	Camera Camera_2;

	Player ThePlayer;
	NPC TheNPC;
	NPC NPC_2;
	NPC NPC_3;
	Door TheDoor;

	PickUpItem item_1;
	PickUpItem item_2;
	PickUpItem item_3;
	PickUpItem item_4;
	PickUpItem item_5;
	PickUpItem item_6;
	PickUpItem item_7;
	PickUpItem item_8;

	Model Floor_1;
	Model Wall_1;
	Model Wall_2;
	Model Wall_3;
	Model Wall_4;
	Model Wall_5;
	Model Roof_1;

	Box box;

	bool Scene_2 = false;
	bool KeyPressed = false;

	void spawn_PickupRandom();
};

