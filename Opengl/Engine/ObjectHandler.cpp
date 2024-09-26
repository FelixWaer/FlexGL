#include "ObjectHandler.h"

void ObjectHandler::update_Positions()
{
	for (size_t i = 0; i < ObjectPositions.size(); i++)
	{
		ObjectPositions[i] += ObjectVelocity;
	}
}

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
	NumberOfGameObjects++;

	return NumberOfGameObjects - 1;
}

void ObjectHandler::remove_ObjectFromHandler(uint32_t objectID)
{
	delete GameObjects[objectID];
	GameObjects[objectID] = nullptr;

	AvailableIDs.emplace(objectID);
}
