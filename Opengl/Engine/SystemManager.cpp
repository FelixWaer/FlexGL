#include "SystemManager.h"

#include "../Systems/System.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/TransformSystem.h"

void SystemManager::init_Systems()
{
	System* mc = new MovementSystem;
	System* tc = new TransformSystem;
	SystemsHandler.emplace_back(mc);
	SystemsHandler.emplace_back(tc);
}

void SystemManager::update_Systems(float deltaTime)
{
	for (System* sys : SystemsHandler)
	{
		sys->update(deltaTime);
	}
}
