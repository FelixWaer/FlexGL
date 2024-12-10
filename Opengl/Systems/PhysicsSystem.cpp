#include "PhysicsSystem.h"

#include "../Components/MovementComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/PositionComponent.h"

void PhysicsSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<PhysicsComponent>() == false ||
		get_ComponentManager().check_IfHandlerExists<PositionComponent>() == false ||
		get_ComponentManager().check_IfHandlerExists<MovementComponent>() == false)
	{
		return;
	}

	ComponentHandler<PhysicsComponent>* physicsComps = get_ComponentHandler<PhysicsComponent>();
	ComponentHandler<MovementComponent>* moveComps = get_ComponentHandler<MovementComponent>();
	ComponentHandler<PositionComponent>* posComps = get_ComponentHandler<PositionComponent>();


	for (auto& index : physicsComps->IndexMap)
	{
		if (posComps->get_Component(index.first).Position.y > 1.f)
		{
			moveComps->get_Component(index.first).Acceleration.y = -physicsComps->get_Component(index.first).gravity;
		}
		else
		{
			posComps->get_Component(index.first).Position.y = 1.f;
		}
	}
}
