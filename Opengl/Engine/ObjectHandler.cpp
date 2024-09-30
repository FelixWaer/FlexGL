#include "ObjectHandler.h"

#include <glm/ext/matrix_transform.hpp>

#include "../FlexLibrary/FlexTimer/Flextimer.h"

void ObjectHandler::tick_Objects(float deltaTime)
{
	for (GameObject* object : GameObjects)
	{
		if (object == nullptr)
		{
			continue;
		}

		object->tick(deltaTime);
	}
}

void ObjectHandler::update_Positions(float deltaTime)
{
	FlexTimer timer("Position Updating");

	for (size_t i = 0; i < ObjectPositions.size(); i++)
	{
		ObjectPositions[i] += ObjectVelocity[i] * deltaTime;
	}
}

uint32_t ObjectHandler::add_ObjectToHandler(GameObject* gameObject)
{
	if (AvailableObjectIDs.empty() == true)
	{
		GameObjects.emplace_back(gameObject);
		ObjectPositions.emplace_back(glm::vec3(0.f));
		ObjectVelocity.emplace_back(glm::vec3(0.f));
		NumberOfGameObjects++;

		return NumberOfGameObjects - 1;
	}

	const uint32_t availableID = AvailableObjectIDs.front();
	AvailableObjectIDs.pop();
	GameObjects[availableID] = gameObject;

	return availableID;
}

void ObjectHandler::remove_ObjectFromHandler(uint32_t objectID)
{
	delete GameObjects[objectID];
	GameObjects[objectID] = nullptr;

	AvailableObjectIDs.emplace(objectID);
}

glm::vec3& ObjectHandler::get_ObjectPosition(uint32_t objectID)
{
	return ObjectPositions[objectID];
}

void ObjectHandler::set_ObjectPosition(uint32_t objectID, const glm::vec3& newPosition)
{
	ObjectPositions[objectID] = newPosition;
}

void ObjectHandler::set_ObjectPosition(uint32_t objectID, const glm::vec3&& newPosition)
{
	ObjectPositions[objectID] = newPosition;
}

glm::vec3& ObjectHandler::get_ObjectVelocity(uint32_t objectID)
{
	return ObjectVelocity[objectID];
}

void ObjectHandler::set_ObjectVelocity(uint32_t objectID, const glm::vec3& newPosition)
{
	ObjectVelocity[objectID] = newPosition;
}

void ObjectHandler::set_ObjectVelocity(uint32_t objectID, const glm::vec3&& newPosition)
{
	ObjectVelocity[objectID] = newPosition;
}
