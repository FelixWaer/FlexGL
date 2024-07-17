#pragma once

#include <iostream>

class GameObject;


class Event
{
public:
	Event() = default;
	virtual void Input_Event() = 0;
	virtual void Collision_Event(GameObject* otherGameObject) = 0;
};

template <typename T>
class EventCallback : public Event
{
public:
	EventCallback(T* instance, void (T::* function)()) : Instance(instance), InputFunction(function){}
	EventCallback(T* instance, void (T::* function)(GameObject*)) : Instance(instance), CollisionFunction(function){}

	void Input_Event() override
	{
		if (InputFunction == nullptr || Instance == nullptr)
		{
			std::cout << "EventCallback is a nullptr" << std::endl;
		}
		else
		{
			(Instance->*InputFunction)();
		}
	}

	void Collision_Event(GameObject* otherGameObject) override
	{
		if (CollisionFunction == nullptr || Instance == nullptr)
		{
			std::cout << "EventCallback is a nullptr" << std::endl;
		}
		else
		{
			(Instance->*CollisionFunction)(otherGameObject);
		}
	}

private:
	T* Instance = nullptr;
	void (T::* InputFunction)() = nullptr;
	void (T::* CollisionFunction)(GameObject*) = nullptr;
};

template <typename T>
Event* make_Event(T* instance, void (T::* function)())
{
	return new EventCallback(instance, function);
}

template <typename T>
Event* make_Event(T* instance, void (T::* function)(GameObject*))
{
	return new EventCallback(instance, function);
}