#include "Input.h"

void Input::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	FKey = false;
	if (key == GLFW_KEY_F && action == GLFW_RELEASE && OldAction == GLFW_PRESS)
	{
		FKey = true;
	}
	OldAction = action;
}
