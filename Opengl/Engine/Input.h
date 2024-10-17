#pragma once

#include <unordered_map>

struct GLFWwindow;
class Event;

enum class Key
{
	W = 87,
	A = 65,
	S = 83,
	D = 68,
	Zero = 48,
	One = 49,
	Two = 50,
	Three = 51,
	ESCAPE = 256,
	LMouse = 0,
	RMouse = 1,
};

enum class KeyPress
{
	OnPress,
	OnRelease,
	WhileHeldDown,
	WhileReleased,
};

class Input
{
public:
	static void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_Callback(GLFWwindow* window, int button, int action, int mods);

	static void bind_EventToKey(Event* eventPtr, Key keyType, KeyPress keyPressType);
	static void call_KeyEvents();
	static void reset_Input();

private:
	static inline std::unordered_map<Key, std::vector<Event*>> EventPressedInputMap;
	static inline std::unordered_map<Key, std::vector<Event*>> EventHeldDownInputMap;
	static inline std::unordered_map<Key, std::vector<Event*>> EventReleasedInputMap;
	static inline std::unordered_map<Key, std::vector<Event*>> EventWhileReleasedInputMap;

	static inline std::unordered_map<Key, bool> KeyPressedMap;
	static inline std::unordered_map<Key, bool> KeyHeldDownMap;
};

