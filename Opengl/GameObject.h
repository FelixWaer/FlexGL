#pragma once
#include "glm/glm.hpp"
#include <iostream>
#include <string>
#include <vector>

class EngineManager;

class GameObject
{
public:
	GameObject() = default;
	void init_GameObject();
	virtual void tick(float deltaTime);
	virtual void game_Start();
	virtual void on_Collision(GameObject* otherGameObject);
	void set_GameObjectPosition(glm::vec3 newPosition);
	glm::vec3 get_GameObjectPosition();
	glm::vec3* get_GameObjectPositionPtr();
	void set_GameObjectVelocity(const glm::vec3& newVelocity);
	glm::vec3& get_GameObjectVelocity();
	void add_Tag(const std::string& tag);
	bool has_Tag(const std::string& tag);

private:
	glm::vec3 GameObjectPosition;
	glm::vec3 GameObjectVelocity;
	std::vector<std::string> tags;
};