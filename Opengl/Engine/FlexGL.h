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


	Player ThePlayer;
	NPC TheNPC;
	NPC NPC_2;
	NPC NPC_3;

	Model SkyBox;

	Terrain theTerrain;

	std::vector<PickUpItem*> items;

	Model TerrainLine;

	bool KeyPressed = false;
	bool KeyPressed2 = false;
	bool DebugTurnedOff = false;

	bool CameraIs1 = true;

	void spawn_PickupRandom();
};

