#include "CollisionSystem.h"

#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"
#include "../Components/PositionComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/DamageComponent.h"

void CollisionSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<PositionComponent>() == false ||
		get_ComponentManager().check_IfHandlerExists<CollisionComponent>() == false)
	{
		return;
	}

	std::vector<PositionComponent>& posComponents = get_ComponentHandler<PositionComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapPos = get_ComponentHandler<PositionComponent>()->IndexMap;

	std::vector<CollisionComponent>& collisionComponents = get_ComponentHandler<CollisionComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapCollision = get_ComponentHandler<CollisionComponent>()->IndexMap;

	std::vector<HealthComponent>& healthComponents = get_ComponentHandler<HealthComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapHealth = get_ComponentHandler<HealthComponent>()->IndexMap;

	std::vector<DamageComponent>& damageComponents = get_ComponentHandler<DamageComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapDamage = get_ComponentHandler<DamageComponent>()->IndexMap;

	for (auto& i : indexMapCollision)
	{
		for (auto& j : indexMapCollision)
		{
			if (i.first == j.first)
			{
				continue;
			}

			float distance = glm::distance(posComponents[indexMapPos[i.first]].Position, posComponents[indexMapPos[j.first]].Position);

			if (distance <= collisionComponents[indexMapCollision[i.first]].Radius + collisionComponents[indexMapCollision[j.first]].Radius)
			{
				healthComponents[indexMapHealth[j.first]].DamageTaken += damageComponents[indexMapDamage[i.first]].Damage;
			}
		}
	}
}
