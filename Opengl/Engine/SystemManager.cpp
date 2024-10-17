#include "SystemManager.h"

#include "../Systems/System.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/TransformSystem.h"
#include "../Systems/CombatSystem.h"
#include "../Systems/CollisionSystem.h"

void SystemManager::init_Systems()
{
	System* ms = new MovementSystem;
	System* ts = new TransformSystem;
	System* cs = new CombatSystem;
	System* collisionSystem = new CollisionSystem;
	SystemsHandler.emplace_back(ms);
	SystemsHandler.emplace_back(ts);
	SystemsHandler.emplace_back(cs);
	SystemsHandler.emplace_back(collisionSystem);
}

void SystemManager::update_Systems(float deltaTime)
{
	for (System* sys : SystemsHandler)
	{
		sys->update(deltaTime);
	}
}
