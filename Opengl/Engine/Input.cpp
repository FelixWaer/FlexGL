#include "Input.h"

#include <iostream>

void Input::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_W:
				Keys[GLFW_KEY_W] = true;
				KeysHeldDown[GLFW_KEY_W] = true;
				break;
			case GLFW_KEY_S:
				Keys[GLFW_KEY_S] = true;
				KeysHeldDown[GLFW_KEY_S] = true;
				break;
			case GLFW_KEY_A:
				Keys[GLFW_KEY_A] = true;
				KeysHeldDown[GLFW_KEY_A] = true;
				break;
			case GLFW_KEY_D:
				Keys[GLFW_KEY_D] = true;
				KeysHeldDown[GLFW_KEY_D] = true;
				break;
			case GLFW_KEY_F:
				Keys[GLFW_KEY_F] = true;
				KeysHeldDown[GLFW_KEY_F] = true;
				break;
			case GLFW_KEY_SPACE:
				Keys[GLFW_KEY_SPACE] = true;
				KeysHeldDown[GLFW_KEY_SPACE] = true;
				break;
			case GLFW_KEY_LEFT_SHIFT:
				Keys[GLFW_KEY_LEFT_SHIFT] = true;
				KeysHeldDown[GLFW_KEY_LEFT_SHIFT] = true;
				break;
			case GLFW_KEY_1:
				Keys[GLFW_KEY_1] = true;
				KeysHeldDown[GLFW_KEY_1] = true;
				break;
			case GLFW_KEY_2:
				Keys[GLFW_KEY_2] = true;
				KeysHeldDown[GLFW_KEY_2] = true;
				break;
			default:
				break;
		}
	}
	if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			KeysHeldDown[GLFW_KEY_W] = false;
			break;
		case GLFW_KEY_S:
			KeysHeldDown[GLFW_KEY_S] = false;
			break;
		case GLFW_KEY_A:
			KeysHeldDown[GLFW_KEY_A] = false;
			break;
		case GLFW_KEY_D:
			KeysHeldDown[GLFW_KEY_D] = false;
			break;
		case GLFW_KEY_F:
			KeysHeldDown[GLFW_KEY_F] = false;
			break;
		case GLFW_KEY_SPACE:
			KeysHeldDown[GLFW_KEY_SPACE] = false;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			KeysHeldDown[GLFW_KEY_LEFT_SHIFT] = false;
			break;
		case GLFW_KEY_1:
			KeysHeldDown[GLFW_KEY_1] = false;
			break;
		case GLFW_KEY_2:
			KeysHeldDown[GLFW_KEY_2] = false;
			break;
		default:
			break;
		}
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

void Input::reset_Keys()
{
	for (int i = 0; i < 341; i++)
	{
		Keys[i] = false;
	}
}

void Input::mouse_Callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_1:
				buttons[GLFW_MOUSE_BUTTON_1] = true;
				buttonsHeldDown[GLFW_MOUSE_BUTTON_1] = true;
				break;
			case GLFW_MOUSE_BUTTON_2:
				buttons[GLFW_MOUSE_BUTTON_2] = true;
				buttonsHeldDown[GLFW_MOUSE_BUTTON_2] = true;
				break;
			default:
				break;
		}
	}
	if (action == GLFW_RELEASE)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_1:
				buttonsHeldDown[GLFW_MOUSE_BUTTON_1] = false;
				break;
			case GLFW_MOUSE_BUTTON_2:
				buttonsHeldDown[GLFW_MOUSE_BUTTON_2] = false;
				break;
			default:
				break;
		}
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

void Input::reset_Buttons()
{
	for (int i = 0; i < 7; i++)
	{
		buttons[i] = false;
	}
}
