#include "ObjectHandler.h"

#include <glm/ext/matrix_transform.hpp>

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

void ObjectHandler::update_Positions()
{
	for (size_t i = 0; i < ObjectPositions.size(); i++)
	{
		ObjectPositions[i] += ObjectVelocity[i];
	}
}

uint32_t ObjectHandler::add_ObjectToHandler(GameObject* gameObject)
{
	if (AvailableIDs.empty() == false)
	{
		uint32_t ID = AvailableIDs.front();
		AvailableIDs.pop();
		GameObjects[ID] = gameObject;

		return ID;
	}

	GameObjects.emplace_back(gameObject);
	ObjectPositions.emplace_back(glm::vec3(0.f));
	ObjectVelocity.emplace_back(glm::vec3(0.f));
	NumberOfGameObjects++;

	return NumberOfGameObjects - 1;
}

void ObjectHandler::remove_ObjectFromHandler(uint32_t objectID)
{
	delete GameObjects[objectID];
	GameObjects[objectID] = nullptr;

	AvailableIDs.emplace(objectID);
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

void ObjectHandler::calculate_ObjectMatrix(uint32_t )
{
	glm::mat4 test(1.f);
	test = glm::translate(glm::mat4(1.f), );
	test *= glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.x), glm::vec3(1.f, 0.f, 0.f));
	test *= glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f));
	test *= glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.z), glm::vec3(0.f, 0.f, 1.f));
	return glm::scale(test, ModelScale);
}
