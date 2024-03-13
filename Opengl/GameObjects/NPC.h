#pragma once
#include "../GameObject.h"
#include "../Model.h"
#include "../GameObject Components/BoxCollision.h"

class NPC : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;

	void enable_CircleDriving(bool enable);

	bool DoNothing = false;
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

	void move_NPC(float deltaTime);
	float calculate_NPCPath(float x);
	void calculate_CirclePath(float deltaTime);
};

