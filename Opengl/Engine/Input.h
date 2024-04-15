#pragma once
#include "GLFW/glfw3.h"

class Input
{
public:
	static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool key_Pressed(int key);
	static void reset_Keys();

private:
	static inline bool Keys[256] = {};
};

