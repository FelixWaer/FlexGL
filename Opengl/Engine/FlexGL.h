#pragma once

#include "../Rendering/Camera.h"
#include "../GameObjects/Door.h"
#include "../GameObjects/PickUpItem.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Graphs.h"
#include "../GameObjects/NPC.h"
#include "../GameObjects/Box.h"
#include "Terrain.h"


class Terrain;
struct GLFWwindow;

class FlexGL
{
public:
	void game_Start();
	void tick(float deltaTime);
	void input(GLFWwindow* window);
private:

	Graphs graph_1;

	std::vector<Camera*> Cameras;
	int CameraIndex = 0;
	Camera Camera_1;
	Camera Camera_2;

	Player ThePlayer;
	NPC TheNPC;
	NPC NPC_2;
	NPC NPC_3;

	Terrain theTerrain;

	std::vector<PickUpItem*> items;
	PickUpItem HouseItem;

	//Model Floor_1;
	//Model Wall_1;
	//Model Wall_2;
	//Model Wall_3;
	//Model Wall_4;
	//Model Wall_5;
	//Model Roof_1;
	//Door TheDoor;

	//Model Terrain;
	Model TerrainLine;

	bool KeyPressed = false;
	bool KeyPressed2 = false;
	bool DebugTurnedOff = false;

	bool CameraIs1 = true;

	void spawn_PickupRandom();
	void spawn_Item();
};

