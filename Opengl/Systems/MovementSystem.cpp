#include "MovementSystem.h"

#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"

void MovementSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<PositionComponent>() == false ||
		get_ComponentManager().check_IfHandlerExists<MovementComponent>() == false)
	{
		return;
	}

	std::vector<PositionComponent>& posComponent = get_ComponentHandler<PositionComponent>()->Components;
	std::vector<MovementComponent>& moveComponent = get_ComponentHandler<MovementComponent>()->Components;

	for (int i = 0; i < moveComponent.size(); i++)
	{
		posComponent[i].Position += moveComponent[i].Direction * moveComponent[i].Speed * deltaTime;
	}
}
