#pragma once

#include <string>
#include <vector>

#include "../Components/ComponentHandler.h"
#include "glm/glm.hpp"

class SceneManager;

class GameObject
{
public:
	GameObject() = default;
	~GameObject() = default;

	void init_GameObject();
	virtual void tick(float deltaTime);
	virtual void game_Start();

	uint32_t get_GameObjectID();
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
	glm::vec3 GameObjectFront = glm::vec3(0.f);
	glm::vec3 TempPosition = glm::vec3(0.f);

	SceneManager* ParentScene = nullptr;

private:
	uint32_t ObjectID = 0;
	std::vector<std::string> tags;
};