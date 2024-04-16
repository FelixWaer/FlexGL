#pragma once
#include "../Engine/GameObject.h"

#include "../Rendering/Camera.h"
#include "../GameObject Components/SphereCollision.h"
#include "../GameObject Components/BoxCollision.h"
#include "../Rendering/Model.h"

class Player : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void on_Collision(GameObject* otherGameObject) override;
	glm::ivec2 get_PlayerChunkPosition() const;

	Camera PlayerCamera;
	Camera FreeCamera;
	SphereCollision SphereCollider;
	BoxCollision BoxCollider;
	Model PlayerModel;

	void jump();
private:
	bool Jumping = false;

	glm::ivec2 ChunkPosition = glm::ivec2(0);

	void spawn_Item();
};

