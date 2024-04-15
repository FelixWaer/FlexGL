#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../GameObject Components/SphereCollision.h"

class Graphs : public GameObject
{
public:
	void tick(float deltaTime) override;
	void game_Start() override;
	void on_Collision(GameObject* otherGameObject) override;

private:
	Model line;
};

