#include "WindowManager.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "EngineManager.h"
#include "Input.h"

double XPosMouse = 0;
double YPosMouse = 0;
bool CameraFirstMove = true;

void WindowManager::init_Window()
{
	WindowPtr = glfwCreateWindow(WindowWidth, WindowHeight, "FlexEngine", nullptr, nullptr);

    if (WindowPtr == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(WindowPtr);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(WindowPtr, WindowManager::resize_Window);
    glfwSetCursorPosCallback(WindowPtr, mouse_Button_Callback);
    glfwSetKeyCallback(WindowPtr, Input::key_Callback);
    glfwSetMouseButtonCallback(WindowPtr, Input::mouse_Callback);
    glfwSetInputMode(WindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowManager::close_Window()
{
    glfwSetWindowShouldClose(WindowPtr, true);
}

GLFWwindow* WindowManager::get_Window()
{
    return WindowPtr;
}

int WindowManager::get_WindowWidth()
{
    return WindowWidth;
}

void WindowManager::set_WindowWidth(int newWindowWidth)
{
    WindowWidth = newWindowWidth;
}

int WindowManager::get_WindowHeight()
{
    return WindowHeight;
}

void WindowManager::set_WindowHeight(int newWindowHeight)
{
    WindowHeight = newWindowHeight;
}

float WindowManager::get_AspectRatio()
{
    return static_cast<float>(WindowWidth) / static_cast<float>(WindowHeight);
}

void WindowManager::resize_Window(GLFWwindow* window, int newWidth, int newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    std::cout << " windows resized with " << newWidth << " Height " << newHeight << std::endl;
    EngineManager::get()->get_ActiveWindow().set_WindowWidth(newWidth);
    EngineManager::get()->get_ActiveWindow().set_WindowHeight(newHeight);
}

void WindowManager::mouse_Button_Callback(GLFWwindow* window, double xPos, double yPos)
{
    if (CameraFirstMove == true)
    {
        XPosMouse = xPos;
        YPosMouse = yPos;
        CameraFirstMove = false;
    }

    float xOffset = xPos - XPosMouse;
    float yOffset = YPosMouse - yPos;
    XPosMouse = xPos;
    YPosMouse = yPos;

    EngineManager::get()->get_ActiveScene()->get_SceneCamera()->update_CameraRotation(xOffset * 0.1f, yOffset * 0.1f);
}
