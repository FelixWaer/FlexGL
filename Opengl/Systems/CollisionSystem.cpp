#include "CollisionSystem.h"

#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"
#include "../Components/PositionComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/DamageComponent.h"
#include "../Components/TagComponent.h"

void CollisionSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<PositionComponent>() == false ||
		get_ComponentManager().check_IfHandlerExists<CollisionComponent>() == false)
	{
		return;
	}

	ComponentHandler<TagComponent>* tagHandler = get_ComponentHandler<TagComponent>();

	std::vector<PositionComponent>& posComponents = get_ComponentHandler<PositionComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapPos = get_ComponentHandler<PositionComponent>()->IndexMap;

	std::vector<CollisionComponent>& collisionComponents = get_ComponentHandler<CollisionComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapCollision = get_ComponentHandler<CollisionComponent>()->IndexMap;

	std::vector<HealthComponent>& healthComponents = get_ComponentHandler<HealthComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapHealth = get_ComponentHandler<HealthComponent>()->IndexMap;

	ComponentHandler<DamageComponent>* damageHandler = get_ComponentHandler<DamageComponent>();
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

			if (tagHandler->get_Component(i.first).Tag == "Player" && tagHandler->get_Component(j.first).Tag == "Enemy"
				|| tagHandler->get_Component(i.first).Tag == "Enemy" && tagHandler->get_Component(j.first).Tag == "Player")
			{
				float distance = glm::distance(posComponents[indexMapPos[i.first]].Position, posComponents[indexMapPos[j.first]].Position);

				if (distance <= collisionComponents[indexMapCollision[i.first]].Radius &&
					damageHandler->get_Component(i.first).CurrentTime >= damageHandler->get_Component(i.first).CooldownTimer)
				{
					healthComponents[indexMapHealth[j.first]].DamageTaken += damageComponents[indexMapDamage[i.first]].Damage;
					damageHandler->get_Component(i.first).CurrentTime = 0.f;
				}
			}
		}
	}
}
