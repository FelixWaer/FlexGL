#pragma once
#include "../GameObject.h"

#include "../Camera.h"
#include "../GameObject Components/SphereCollision.h"
#include "../GameObject Components/BoxCollision.h"
#include "../Model.h"

class Player : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void on_Collision(GameObject* otherGameObject) override;

	Camera TheCamera;
	//SphereCollision SphereCollider;
	BoxCollision BoxCollider;
	Model PlayerModel;

	void jump();
private:
	bool Jumping = false;
};

