#include "EntityManager.h"

#include "../GameObjects/entity.h"

uint32_t EntityManager::add_EntityToScene(Entity* entity)
{
	if (AvailableEntityIDs.empty() == false)
	{
		EntityID availableID = AvailableEntityIDs.front();
		AvailableEntityIDs.pop();
		SceneEntities[availableID] = entity;

		return availableID;
	}

    SceneEntities.emplace_back(entity);

    return SceneEntities.size();
}

void EntityManager::remove_EntityFromScene(EntityID entityID)
{
	delete SceneEntities[entityID];
	SceneEntities[entityID] = nullptr;

	AvailableEntityIDs.emplace(entityID);
}
