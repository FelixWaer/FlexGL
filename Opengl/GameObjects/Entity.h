#pragma once
#include "../Engine/EngineManager.h"
#include "../Engine/ComponentManager.h"

using EntityID = uint32_t;

class Entity
{
public:
	void create_Entity();

	virtual void tick(float deltaTime);

	EntityID get_EntityID();

	template <typename T>
	void add_Component()
	{
		EngineManager::get()->get_ActiveScene()->get_ComponentManager().add_Component<T>(ID);
	}

	template <typename T>
	T& get_Component()
	{
		return EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_Component<T>(ID);
	}

	template <typename T>
	bool has_Component()
	{
		return EngineManager::get()->get_ActiveScene()->get_ComponentManager().get_ComponentHandler<T>()->IndexMap.contains(ID);
	}

	Entity* ParentID = nullptr;
	std::vector<Entity*> Children;
protected:
	virtual void init_Entity();
	void enable_Ticking();

private:
	EntityID ID = 0;
};

