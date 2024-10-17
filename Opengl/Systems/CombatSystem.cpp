#include "CombatSystem.h"

#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"
#include "../Components/HealthComponent.h"

void CombatSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<HealthComponent>() == false)
	{
		return;
	}

	std::vector<HealthComponent>& healthComponent = get_ComponentHandler<HealthComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMap = get_ComponentHandler<HealthComponent>()->IndexMap;

	for (int i = 0; i < healthComponent.size(); i++)
	{
		if (healthComponent[i].DamageTaken > 0.f)
		{
			healthComponent[i].Health -= healthComponent[i].DamageTaken;
			//std::cout << "Damage taken: " << healthComponent[i].DamageTaken << std::endl;
			healthComponent[i].DamageTaken = 0.f;
		}
	}
}
