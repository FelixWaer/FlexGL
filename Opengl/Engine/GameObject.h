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
	glm::vec3& get_GameObjectPosition();
	glm::vec3* get_GameObjectPositionPtr();
	void set_GameObjectVelocity(const glm::vec3& newVelocity);
	glm::vec3& get_GameObjectVelocity();
	void set_GameObjectFront(const glm::vec3& newFront);
	glm::vec3& get_GameObjectFront();
	void add_Tag(const std::string& tag);
	bool has_Tag(const std::string& tag);
protected:
	glm::vec3 GameObjectPosition = glm::vec3(0.f);
	glm::vec3 GameObjectVelocity = glm::vec3(0.f);
	glm::vec3 GameObjectFront = glm::vec3(0.f);

private:
	std::vector<std::string> tags;
};