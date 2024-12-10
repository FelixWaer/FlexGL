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

	Timer += deltaTime;

	std::vector<PositionComponent>& posComponent = get_ComponentHandler<PositionComponent>()->Components;
	std::vector<MovementComponent>& moveComponent = get_ComponentHandler<MovementComponent>()->Components;

	for (int i = 0; i < moveComponent.size(); i++)
	{
		moveComponent[i].Velocity += moveComponent[i].Acceleration * deltaTime;
		posComponent[i].Position += moveComponent[i].Velocity * deltaTime;
		moveComponent[i].Acceleration = glm::vec3(0.f);

		if (Timer >= 0.1f)
		{
			moveComponent[i].Velocity *= 0.9f;
		}
	}

	if (Timer >= 0.1f)
	{
		Timer = 0.f;
	}
}
