#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../GameObject Components/SphereCollision.h"

class Grid : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;

	void test(glm::ivec2 tileCord);

private:
	Model GridModel;
	//SphereCollision collider;
};

