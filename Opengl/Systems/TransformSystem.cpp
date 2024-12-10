#include "TransformSystem.h"

#include <glm/ext/matrix_transform.hpp>

#include "../Components/ComponentHandler.h"
#include "../Components/PositionComponent.h"
#include "../Components/TransformComponent.h"

void TransformSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<PositionComponent>() == false || 
		get_ComponentManager().check_IfHandlerExists<TransformComponent>() == false)
	{
		return;
	}

	std::vector<PositionComponent>& posComponents = get_ComponentHandler<PositionComponent>()->Components;
	std::vector<TransformComponent>& transComponents = get_ComponentHandler<TransformComponent>()->Components;

	for (size_t i = 0; i < transComponents.size(); i++)
	{
		transComponents[i].Matrix = glm::translate(glm::mat4(1.f), posComponents[i].Position);
		transComponents[i].Matrix = glm::rotate(transComponents[i].Matrix, transComponents[i].Rotation.x, glm::vec3(1.f, 0.f, 0.f));
		transComponents[i].Matrix = glm::rotate(transComponents[i].Matrix, transComponents[i].Rotation.y, glm::vec3(0.f, 1.f, 0.f));
		transComponents[i].Matrix = glm::rotate(transComponents[i].Matrix, transComponents[i].Rotation.z, glm::vec3(0.f, 0.f, 1.f));
		transComponents[i].Matrix = glm::scale(transComponents[i].Matrix, transComponents[i].Scale);
	}
}
