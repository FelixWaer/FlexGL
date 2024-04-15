#pragma once
#include "GLFW/glfw3.h"

class Input
{
public:
	static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	inline static bool FKey = false;
	inline static int OldAction = GLFW_RELEASE;
};

