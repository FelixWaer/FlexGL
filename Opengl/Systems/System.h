#pragma once
#include "../Engine/EngineManager.h"
#include "../Components/ComponentHandler.h"

class System
{
protected:
	template <typename T>
	ComponentHandler<T>* get_ComponentHandler()
	{
		return EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<T>();
	}
};
