#include "SystemManager.h"

#include "../Systems/System.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/TransformSystem.h"
#include "../Systems/CombatSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/ParticleSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/LuaSystem.h"

void SystemManager::init_Systems()
{
	System* luaSystem = new LuaSystem;
	System* ms = new MovementSystem;
	System* ts = new TransformSystem;
	System* cs = new CombatSystem;
	System* collisionSystem = new CollisionSystem;
	System* particleSystem = new ParticleSystem;
	System* physicsSystem = new PhysicsSystem;
	particleSystem->init();
	SystemsHandler.emplace_back(ms);
	SystemsHandler.emplace_back(ts);
	SystemsHandler.emplace_back(cs);
	SystemsHandler.emplace_back(collisionSystem);
	SystemsHandler.emplace_back(particleSystem);
	SystemsHandler.emplace_back(physicsSystem);
	SystemsHandler.emplace_back(luaSystem);
}

void SystemManager::update_Systems(float deltaTime)
{
	for (System* sys : SystemsHandler)
	{
		sys->update(deltaTime);
	}
}
