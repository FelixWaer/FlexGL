#pragma once
#include <queue>
#include <vector>

class Entity;

using EntityID = uint32_t;

class EntityManager
{
public:
	uint32_t add_EntityToScene(Entity* entity);
	void remove_EntityFromScene(EntityID entityID);
private:
	std::vector<Entity*> SceneEntities;
	std::queue<EntityID> AvailableEntityIDs;
	uint32_t TotalEntities = 0;
};

