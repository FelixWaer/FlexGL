#include "Input.h"

#include <ranges>
#include <GLFW/glfw3.h>

#include "EventCallback.h"

void Input::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Key keyType = static_cast<Key>(key);

	if (action == GLFW_PRESS)
	{
		if (EventPressedInputMap.contains(keyType) == true)
		{
			KeyPressedMap[keyType] = true;
			for (Event* event : EventPressedInputMap[keyType])
			{
				event->Input_Event();
			}
		}

		if (KeyHeldDownMap.contains(keyType) == true)
		{
			KeyHeldDownMap[keyType] = true;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (EventReleasedInputMap.contains(keyType) == true)
		{
			for (Event* event : EventReleasedInputMap[keyType])
			{
				event->Input_Event();
			}
		}

		if (KeyHeldDownMap.contains(keyType) == true)
		{
			KeyHeldDownMap[keyType] = false;
		}
	}
}

void Input::mouse_Callback(GLFWwindow* window, int button, int action, int mods)
{
	Key keyType = static_cast<Key>(button);

	if (action == GLFW_PRESS)
	{
		if (EventPressedInputMap.contains(keyType) == true)
		{
			KeyPressedMap[keyType] = true;
			for (Event* event : EventPressedInputMap[keyType])
			{
				event->Input_Event();
			}
		}

		if (KeyHeldDownMap.contains(keyType) == true)
		{
			KeyHeldDownMap[keyType] = true;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (EventReleasedInputMap.contains(keyType) == true)
		{
			for (Event* event : EventReleasedInputMap[keyType])
			{
				event->Input_Event();
			}
		}

		if (KeyHeldDownMap.contains(keyType) == true)
		{
			KeyHeldDownMap[keyType] = false;
		}
	}
}

void Input::bind_EventToKey(Event* eventPtr, Key keyType, KeyPress keyPressType)
{
	switch (keyPressType)
	{
	case KeyPress::OnPress:
		EventPressedInputMap[keyType].emplace_back(eventPtr);
		KeyPressedMap[keyType] = false;
		break;

	case KeyPress::WhileHeldDown:
		EventHeldDownInputMap[keyType].emplace_back(eventPtr);
		KeyHeldDownMap[keyType] = false;
		break;

	case KeyPress::OnRelease:
		EventReleasedInputMap[keyType].emplace_back(eventPtr);
		break;

	case KeyPress::WhileReleased:
		EventWhileReleasedInputMap[keyType].emplace_back(eventPtr);
		break;
	}
}

void Input::call_KeyEvents()
{
	for (auto& KeyEvents : EventHeldDownInputMap)
	{
		if (KeyHeldDownMap[KeyEvents.first] == true)
		{
			for (Event* event : KeyEvents.second)
			{
				event->Input_Event();
			}
		}
	}

	for (auto& KeyEvents : EventWhileReleasedInputMap)
	{
		if (KeyHeldDownMap[KeyEvents.first] == false)
		{
			for (Event* event : KeyEvents.second)
			{
				event->Input_Event();
			}
		}
	}
}

void Input::reset_Input()
{
	for (auto& key : KeyPressedMap)
	{
		key.second = false;
	}
}

