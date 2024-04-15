#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../GameObject Components/BoxCollision.h"

class NPC : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;

	void enable_CircleDriving(bool enable);
	void move_UpDown();
	bool DoNothing = false;
	void switch_Path();
private:
	Model NPCModel;
	BoxCollision BoxCollider;

	float xPos = -10.f;
	float xDirection = 1.f;
	float NPCSpeed = 10.f;
	float Degrees = 0.f;
	float Radius = 15.f;
	float SmallerBigger = 1.f;
	bool CircleDriving = false;
	bool OriginalePath = true;

	void move_NPC(float deltaTime);
	float calculate_NPCPath(float x);
	void calculate_CirclePath(float deltaTime);
	void calculate_Height();
};

