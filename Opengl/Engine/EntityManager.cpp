#include "EntityManager.h"

#include "../GameObjects/entity.h"

void EntityManager::tick_Entities(float deltaTime)
{
	for (Entity* entity : EntitiesTicking)
	{
		entity->tick(deltaTime);
	}
}

void EntityManager::enable_EntityToTick(Entity* entity)
{
	EntitiesTicking.emplace_back(entity);
}

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
	for (int i = 0; i < EntitiesTicking.size(); i++)
	{
		if (EntitiesTicking[i]->get_EntityID() == entityID)
		{
			EntitiesTicking.erase(EntitiesTicking.begin() + i);
		}
	}

	delete SceneEntities[entityID];
	SceneEntities[entityID] = nullptr;

	AvailableEntityIDs.emplace(entityID);
}

Entity* EntityManager::get_Entity(EntityID entityID)
{
	return SceneEntities[entityID];
}

void SceneGraph::add_Child(EntityID parentID, EntityID childID)
{

}

void SceneGraph::remove_Child(EntityID childID)
{
}

void SceneGraph::remove_Parent(EntityID parentID)
{
}

void SceneGraph::add_ChildTraversal(Entity* node, EntityID parentID, EntityID childID)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->get_EntityID() == parentID)
	{
		node->Children.emplace_back(EM->get_Entity(childID));

		return;
	}

	for (Entity* child : node->Children)
	{
		add_ChildTraversal(child, parentID, childID);
	}
}
