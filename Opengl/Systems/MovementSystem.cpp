#include "MovementSystem.h"

#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"

void MovementSystem::update(float deltaTime)
{
	ComponentHandler<PositionComponent>* posComponent = get_ComponentHandler<PositionComponent>();
	ComponentHandler<MovementComponent>* moveComponent = get_ComponentHandler<MovementComponent>();

	for (const std::pair<EntityID, uint32_t> index : moveComponent->IndexMap)
	{
		posComponent->Components[posComponent->IndexMap[index.first]].Position += moveComponent->Components[index.second].Direction
		* (moveComponent->Components[index.second].Direction * deltaTime);
	}
}
