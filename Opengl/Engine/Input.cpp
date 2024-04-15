#include "Input.h"

#include <iostream>

void Input::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_F:
				Keys[GLFW_KEY_F] = true;
			break;
		}
	}
}

bool Input::key_Pressed(int key)
{
	return Keys[key];
}

void Input::reset_Keys()
{
	for (int i = 0; i < 256; i++)
	{
		Keys[i] = false;
	}
}
