#pragma once
#include <queue>
#include <vector>

class Entity;

using EntityID = uint32_t;

class EntityManager
{
public:
	void tick_Entities(float deltaTime);
	void enable_EntityToTick(Entity* entity);
	uint32_t add_EntityToScene(Entity* entity);
	void remove_EntityFromScene(EntityID entityID);
	Entity* get_Entity(EntityID entityID);

private:
	std::vector<Entity*> SceneEntities;
	std::vector<Entity*> EntitiesTicking;
	std::queue<EntityID> AvailableEntityIDs;
	uint32_t TotalEntities = 0;
};

class SceneGraph
{
public:
	SceneGraph(EntityManager* entityManager) : EM(entityManager){}

	EntityManager* EM = nullptr;
	Entity* RootNode = nullptr;

	void add_Child(EntityID parentID, EntityID childID);
	void remove_Child(EntityID childID);
	void remove_Parent(EntityID parentID);

private:
	void add_ChildTraversal(Entity* node, EntityID parentID, EntityID childID);
};
