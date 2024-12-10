#include "CollisionSystem.h"

#include "MovementSystem.h"
#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"
#include "../Components/PositionComponent.h"
#include "../Components/SphereCollComponent.h"
#include "../Components/BoxCollComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/DamageComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TagComponent.h"

void CollisionSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<PositionComponent>() == false ||
		get_ComponentManager().check_IfHandlerExists<SphereCollComponent>() == false)
	{
		return;
	}

	ComponentHandler<PositionComponent>* posComps = get_ComponentHandler<PositionComponent>();
	ComponentHandler<MovementComponent>* moveComps = get_ComponentHandler<MovementComponent>();
	ComponentHandler<TagComponent>* tagComps = get_ComponentHandler<TagComponent>();

	std::vector<SphereCollComponent>& collisionComponents = get_ComponentHandler<SphereCollComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMapCollision = get_ComponentHandler<SphereCollComponent>()->IndexMap;

	for (auto& indexA : indexMapCollision)
	{
		for (auto& indexB : indexMapCollision)
		{
			if (indexA.first == indexB.first)
			{
				continue;
			}

			if (calculate_SphereCollision(posComps->get_Component(indexA.first).Position, collisionComponents[indexA.second].Radius, 
					posComps->get_Component(indexB.first).Position, collisionComponents[indexB.second].Radius) == true)
			{
				glm::vec3 newDirection = posComps->get_Component(indexB.first).Position - posComps->get_Component(indexA.first).Position;

				if (tagComps->get_Component(indexA.first).Tag != "Player")
				{
					moveComps->get_Component(indexA.first).Velocity = glm::normalize(-newDirection) * glm::length(moveComps->get_Component(indexB.first).Velocity);
				}
				else if (tagComps->get_Component(indexB.first).Tag != "Player")
				{
					moveComps->get_Component(indexB.first).Velocity = glm::normalize(newDirection) * glm::length(moveComps->get_Component(indexA.first).Velocity);
				}
			}
		}
	}
}

bool CollisionSystem::calculate_SphereCollision(glm::vec3& sphereA, float radiusA, glm::vec3& sphereB, float radiusB)
{
	float distance = glm::distance(sphereA, sphereB);

	if (distance <= radiusA + radiusB)
	{
		return true;
	}

	return false;
}

bool CollisionSystem::calculate_BoxCollsion()
{
	return false;
}