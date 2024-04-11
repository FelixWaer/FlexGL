#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../GameObject Components/SphereCollision.h"

class PickUpItem : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void on_Collision(GameObject* otherGameObject) override;
	void update_Position(glm::vec3 newPosition);
	void set_Color(const glm::vec3& color);

private:
	Model* ItemModel = nullptr;
	SphereCollision Collider;

	glm::vec3 Color = glm::vec3(0.7f, 0.f, 1.f);
};

