#pragma once
#include "GLFW/glfw3.h"

class Input
{
public:
	static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool key_Pressed(int key);
	static bool key_HeldDown(int key);
	static void reset_Keys();

	static void mouse_Callback(GLFWwindow* window, int button, int action, int mods);
	static bool mouse_Pressed(int button);
	static bool mouse_HeldDown(int button);
	static void reset_Buttons();

private:
	static inline bool Keys[256] = {};
	static inline bool KeysHeldDown[256] = {};

	static inline bool buttons[7] = {};
	static inline bool buttonsHeldDown[7] = {};

};

