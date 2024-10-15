#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using EntityID = uint32_t;

class IComponentHandler
{
public:
	virtual void add_Component(EntityID id);
};

template <typename T>
class ComponentHandler : IComponentHandler
{
public:
	void add_Component(EntityID id) override
	{
		if (IndexMap.contains(id) == true)
		{
			std::cout << "Entity: " << id << "Already contains this Component!" << std::endl;
			return;
		}
		Components.emplace_back();
		IndexMap[id] = Components.size() - 1;
	}

	std::vector<T> Components;
	std::unordered_map<EntityID, uint32_t> IndexMap;
};