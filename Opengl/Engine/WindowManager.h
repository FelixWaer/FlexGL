#pragma once

struct GLFWwindow;

class WindowManager
{
public:
	void init_Window();
	void close_Window();

	GLFWwindow* get_Window();

	int get_WindowWidth();
	void set_WindowWidth(int newWindowWidth);
	int get_WindowHeight();
	void set_WindowHeight(int newWindowHeight);
	float get_AspectRatio();
private:
	GLFWwindow* WindowPtr = nullptr;

	int WindowWidth = 1920;
	int WindowHeight = 1080;

	static void resize_Window(GLFWwindow* window, int newWidth, int newHeight);
	static void mouse_Button_Callback(GLFWwindow* window, double xPos, double yPos);
};

