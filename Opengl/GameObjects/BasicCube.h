#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../GameObject Components/SphereCollision.h"

class BasicCube : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;

private:
	Model Cube;
	//SphereCollision collider;
};

