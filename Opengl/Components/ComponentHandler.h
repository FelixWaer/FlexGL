#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

using EntityID = uint32_t;

class IComponentHandler
{
public:
	virtual void add_Component(EntityID id) = 0;
	virtual void remove_Component(EntityID id) = 0;
};

template <typename T>
class ComponentHandler : public IComponentHandler
{
public:
	void add_Component(EntityID id) override
	{
		if (IndexMap.contains(id) == true)
		{
			//std::cout << "Entity: " << id << "Already contains this Component!" << std::endl;
			return;
		}
		Components.emplace_back();
		IndexMap[id] = Components.size() - 1;

	}

	void remove_Component(EntityID id) override
	{
		if (IndexMap.contains(id) == true)
		{
			int index = IndexMap[id];
			Components.erase(Components.begin() + index);
			IndexMap.erase(id);

			move_Components(index);
		}
	}

	T& get_Component(EntityID id)
	{
		if (IndexMap.contains(id) == true)
		{
			return Components[IndexMap[id]];
		}

		T temp;
		return temp;
	}

	std::vector<T> Components;
	std::unordered_map<EntityID, uint32_t> IndexMap;

private:
	void move_Components(int removedIndex)
	{
		for (auto& index : IndexMap)
		{
			if (index.second > removedIndex)
			{
				index.second--;
			}
		}
	}
};
