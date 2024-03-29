#pragma once
#include "../GameObject.h"
#include "../Model.h"
#include "../GameObject Components/SphereCollision.h"
#include "../GameObject Components/BoxCollision.h"

class PickUpItem : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void on_Collision(GameObject* otherGameObject) override;
	void update_Position(glm::vec3 newPosition);
	void set_Color(const glm::vec3& color);

private:
	Model Model;
	SphereCollision Collider;

	glm::vec3 Color = glm::vec3(1.f, 0.f, 0.f);
};

