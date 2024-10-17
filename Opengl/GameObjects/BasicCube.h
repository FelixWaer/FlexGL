#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../GameObject Components/SphereCollision.h"

class BasicCube : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void init_Entity();

	void update_Position(glm::vec3 newPosition);
	void set_Material(std::string materialName);

private:
	//Model Cube;
	//SphereCollision collider;
};

