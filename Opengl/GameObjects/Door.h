#pragma once
#include "../GameObject.h"
#include "../GameObject Components/SphereCollision.h"
#include "../Model.h"

class Door : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void on_Collision(GameObject* otherGameObject) override;
private:
	Model DoorModel;
	SphereCollision SphereCollider;

	bool OpenDoor = false;

	void move_Door(float deltaTime);
	glm::vec3 Velocity;
};

