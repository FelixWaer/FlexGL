#include "Entity.h"

#include "../Engine/EntityManager.h"

void Entity::create_Enity()
{
	ID = EngineManager::get()->get_ActiveScene()->get_EntityManager().add_EntityToScene(this);
	init_Entity();
}

EntityID Entity::get_EntityID()
{
	return ID;
}

void Entity::init_Entity()
{

}