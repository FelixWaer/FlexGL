#include "LuaSystem.h"

#include "../Components/ScriptComponent.h"

void LuaSystem::update(float deltaTime)
{
	ComponentHandler<ScriptComponent>* scriptComps = get_ComponentHandler<ScriptComponent>();

	for (auto& index : scriptComps->IndexMap)
	{
		EngineManager::get()->get_LuaManager().run_Script(scriptComps->Components[index.second].ScriptPath, index.first);
	}
}
