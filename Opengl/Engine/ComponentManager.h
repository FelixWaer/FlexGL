#pragma once
#include <unordered_map>
#include <string>

#include "../Components/ComponentHandler.h"


class ComponentManager
{
public:
	template <typename T>
	void add_Component(EntityID id)
	{
		if (ComponentHandlers.contains(typeid(T).name()) == false)
		{
			add_ComponentHandler<T>();
		}

		ComponentHandlers[typeid(T).name()]->add_Component(id);
	}

	void add_Component(const std::string& componentName, EntityID id)
	{
		if (ComponentHandlers.contains(componentName) == true)
		{
			ComponentHandlers[componentName]->add_Component(id);
		}
	}

	template <typename T>
	void remove_Component(EntityID id)
	{
		if (ComponentHandlers.contains(typeid(T).name()) == true)
		{
			ComponentHandlers[typeid(T).name()]->remove_Component(id);
		}
	}

	void remove_Component(const std::string& componentName, EntityID id)
	{
		if (ComponentHandlers.contains(componentName) == true)
		{
			ComponentHandlers[componentName]->remove_Component(id);
		}
	}

	template <typename T>
	T& get_Component(EntityID id)
	{
		if (ComponentHandlers.contains(typeid(T).name()) == false)
		{
			std::cout << "Failed at: " << __func__ << " ComponentHandler does not contain this Component Type" << std::endl;
			T temp;
			return temp;
		}
		ComponentHandler<T>* CH = dynamic_cast<ComponentHandler<T>*>(ComponentHandlers[typeid(T).name()]);
		return CH->Components[CH->IndexMap[id]];
	}

	template <typename T>
	ComponentHandler<T>* get_ComponentHandler()
	{
		if (ComponentHandlers.contains(typeid(T).name()) == false)
		{
			std::cout << "Failed at: " << __func__ << " ComponentHandler does not contain this Component Type" << std::endl;
			return nullptr;
		}
		return dynamic_cast<ComponentHandler<T>*>(ComponentHandlers[typeid(T).name()]);
	}

	template <typename T>
	bool check_IfHandlerExists()
	{
		return ComponentHandlers.contains(typeid(T).name());
	}

private:
	std::unordered_map<std::string, IComponentHandler*> ComponentHandlers;

	template <typename T>
	void add_ComponentHandler()
	{
		ComponentHandlers[typeid(T).name()] = new ComponentHandler<T>();
	}
};
