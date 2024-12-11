#include "EntityManager.h"

#include "../Components/TransformComponent.h"
#include "../GameObjects/entity.h"

void EntityManager::tick_Entities(float deltaTime)
{
	for (Entity* entity : EntitiesTicking)
	{
		entity->tick(deltaTime);
	}

	SceneGraphPtr->update_Matrices();
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

    return SceneEntities.size() - 1;
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

void SceneGraph::update_Matrices()
{
	if (RootNode != nullptr)
	{
		calculate_Matrices(RootNode);
	}
}

void SceneGraph::add_Child(EntityID parentID, EntityID childID)
{
	EM->get_Entity(parentID)->Children.emplace_back(EM->get_Entity(childID));
	EM->get_Entity(childID)->ParentID = EM->get_Entity(parentID);
}

void SceneGraph::remove_Child(EntityID childID)
{
	Entity* childPtr = EM->get_Entity(childID);
	Entity* parentPtr = childPtr->ParentID;

	if (parentPtr == nullptr)
	{
		return;
	}
	int index = 0;

	for (Entity* child : parentPtr->Children)
	{
		if (child == childPtr)
		{
			parentPtr->Children.erase(parentPtr->Children.begin() + index);
			break;
		}
		index++;
	}
	
	childPtr->ParentID = nullptr;
}

void SceneGraph::remove_Parent(EntityID parentID)
{
	Entity* parentPtr = EM->get_Entity(parentID);

	for (Entity* child : parentPtr->Children)
	{
		child->ParentID = nullptr;
	}

	parentPtr->Children.clear();
}

void SceneGraph::delete_Child(EntityID childID)
{
}

void SceneGraph::delete_Parent(EntityID parentID)
{
}

void SceneGraph::calculate_Matrices(Entity* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->has_Component<TransformComponent>() == true && node->ParentID->has_Component<TransformComponent>() == true)
	{
		node->get_Component<TransformComponent>().Matrix = node->ParentID->get_Component<TransformComponent>().Matrix * node->get_Component<TransformComponent>().Matrix;
	}


	for (Entity* child : node->Children)
	{
		calculate_Matrices(child);
	}
}
