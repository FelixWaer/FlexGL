#pragma once
#include <queue>
#include <glm/glm.hpp>

#include "GameObject.h"

class ObjectHandler
{
public:
	void tick_Objects(float deltaTime);
	void update_Positions(float deltaTime);

	uint32_t add_ObjectToHandler(GameObject* gameObject);
	void remove_ObjectFromHandler(uint32_t objectID);
	glm::vec3& get_ObjectPosition(uint32_t objectID);
	void set_ObjectPosition(uint32_t objectID, const glm::vec3& newPosition);
	void set_ObjectPosition(uint32_t objectID, const glm::vec3&& newPosition);
	glm::vec3& get_ObjectVelocity(uint32_t objectID);
	void set_ObjectVelocity(uint32_t objectID, const glm::vec3& newPosition);
	void set_ObjectVelocity(uint32_t objectID, const glm::vec3&& newPosition);

private:
	std::vector<GameObject*> GameObjects;
	std::vector<glm::vec3> ObjectPositions;
	std::vector<glm::vec3> ObjectVelocity;
	std::queue<uint32_t> AvailableObjectIDs;

	uint32_t NumberOfGameObjects = 0;
};

