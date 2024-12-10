#include "Entity.h"

#include "../Engine/EntityManager.h"

void Entity::create_Entity()
{
	ID = EngineManager::get()->get_ActiveScene()->get_EntityManager().add_EntityToScene(this);
	init_Entity();
}

void Entity::tick(float deltaTime)
{
}

EntityID Entity::get_EntityID()
{
	return ID;
}

void Entity::init_Entity()
{

}

void Entity::enable_Ticking()
{
	EngineManager::get()->get_ActiveScene()->get_EntityManager().enable_EntityToTick(this);
}
