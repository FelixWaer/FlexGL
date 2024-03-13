#pragma once
#include "../GameObject.h"
#include "../GameObject Components/BoxCollision.h"
#include "../Model.h"

class Box : public GameObject
{
public:
	void game_Start() override;
	void on_Collision(GameObject* otherGameObject) override;

private:
	Model BoxModel;
	BoxCollision BoxCollider;
};

