#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Rendering/Camera.h"
#include "Engine/Terrain.h"

#include "Engine/EngineManager.h"
#include "Engine/Input.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_Button_Callback(GLFWwindow*, double xPos, double yPos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float DeltaTime = 0.f;
float LastFrame = 0.f;

double XPosMouse = SCR_WIDTH / 2;
double YPosMouse = SCR_HEIGHT / 2;
bool CameraFirstMove = true;

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
int main()
{
    EngineManager* EM = EngineManager::get_Engine();
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // to make this portable for other Devices/ operating system MacOS
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    EM->init_Window();

    if (EM->TheWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(EM->TheWindow);
    glfwSwapInterval(0);
    glfwSetFramebufferSizeCallback(EM->TheWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(EM->TheWindow, mouse_Button_Callback);
    glfwSetKeyCallback(EM->TheWindow, Input::key_Callback);
    glfwSetMouseButtonCallback(EM->TheWindow, Input::mouse_Callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(EM->TheWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    EM->init_Engine();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(EM->TheWindow))
    {
        EM->tick_Engine();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(EM->TheWindow);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    std::cout << Terrain::get_Terrain()->TotalAmountOfChunks << std::endl;

    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    std::cout << " windows resized with " << width << " Height " << height << std::endl;
}

void mouse_Button_Callback(GLFWwindow* window, double xPos, double yPos)
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

    EngineManager::get_Engine()->get_ActiveCamera().update_CameraRotation(xOffset * 0.1f, yOffset * 0.1f);
}
