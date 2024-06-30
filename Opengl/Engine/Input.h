#pragma once
#include "GLFW/glfw3.h"

class Input
{
public:
	static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool key_Pressed(int key);
	static bool key_HeldDown(int key);
	static void reset_Input();

	static void mouse_Callback(GLFWwindow* window, int button, int action, int mods);
	static bool mouse_Pressed(int button);
	static bool mouse_HeldDown(int button);

private:
	static inline bool Keys[349] = {};
	static inline bool KeysHeldDown[349] = {};

	static inline bool buttons[8] = {};
	static inline bool buttonsHeldDown[8] = {};

};

