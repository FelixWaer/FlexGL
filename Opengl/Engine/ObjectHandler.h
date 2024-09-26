#pragma once
#include <queue>
#include <glm/glm.hpp>

#include "GameObject.h"

class ObjectHandler
{
public:
	void update_Positions();
	void tick_Objects(float deltaTime);

	uint32_t add_ObjectToHandler(GameObject* gameObject);
	void remove_ObjectFromHandler(uint32_t objectID);

private:
	std::vector<GameObject*> GameObjects;
	std::vector<glm::vec3> ObjectPositions;
	std::vector<glm::vec3> ObjectVelocity;
	std::queue<uint32_t> AvailableIDs;

	uint32_t NumberOfGameObjects = 0;
};

