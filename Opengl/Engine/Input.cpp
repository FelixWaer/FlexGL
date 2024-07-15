#include "Input.h"

#include <iostream>

void Input::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Keys[key] = true;
		KeysHeldDown[key] = true;
	}
	if (action == GLFW_RELEASE)
	{
		KeysHeldDown[key] = false;
	}
}

bool Input::key_Pressed(int key)
{
	return Keys[key];
}

bool Input::key_HeldDown(int key)
{
	return KeysHeldDown[key];
}

void Input::reset_Input()
{
	for (int i = 0; i < 349; i++)
	{
		Keys[i] = false;
	}
	for (int i = 0; i < 8; i++)
	{
		buttons[i] = false;
	}
}

void Input::mouse_Callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		buttons[button] = true;
		buttonsHeldDown[button] = true;
	}
	if (action == GLFW_RELEASE)
	{
		buttonsHeldDown[button] = false;
	}
}

bool Input::mouse_Pressed(int button)
{
	return buttons[button];
}

bool Input::mouse_HeldDown(int button)
{
	return buttonsHeldDown[button];
}

