#include "CombatSystem.h"

#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"
#include "../Components/DamageComponent.h"
#include "../Components/HealthComponent.h"
#include "..\Components\MeshComponent.h"
#include "../Components/TagComponent.h"

void CombatSystem::update(float deltaTime)
{
	if (get_ComponentManager().check_IfHandlerExists<HealthComponent>() == false)
	{
		return;
	}
	ComponentHandler<MeshComponent>* spriteComponents = get_ComponentHandler<MeshComponent>();
	ComponentHandler<TagComponent>* tagHandler = get_ComponentHandler<TagComponent>();

	std::vector<HealthComponent>& healthComponent = get_ComponentHandler<HealthComponent>()->Components;
	std::unordered_map<EntityID, uint32_t>& indexMap = get_ComponentHandler<HealthComponent>()->IndexMap;

	std::vector<DamageComponent>& damageComponents = get_ComponentHandler<DamageComponent>()->Components;

	for (int i = 0; i < healthComponent.size(); i++)
	{
		if (healthComponent[i].DamageTaken > 0.f)
		{
			healthComponent[i].Health -= healthComponent[i].DamageTaken;
			//std::cout << "Damage taken: " << healthComponent[i].DamageTaken << std::endl;
			healthComponent[i].DamageTaken = 0.f;
		}
	}

	for (auto& element : indexMap)
	{
		if (healthComponent[element.second].Health <= 0.f)
		{
			spriteComponents->get_Component(element.first).Render = false;
			tagHandler->get_Component(element.first).Tag = "Dead";
		}
	}

	for (DamageComponent& dc : damageComponents)
	{
		if (dc.CurrentTime <= dc.CooldownTimer)
		{
			dc.CurrentTime += deltaTime;
		}
	}
}
