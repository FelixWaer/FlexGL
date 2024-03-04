#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_Button_Callback(GLFWwindow*, double xPos, double yPos);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float DeltaTime = 0.f;
float LastFrame = 0.f;

double XPosMouse = SCR_WIDTH / 2;
double YPosMouse = SCR_HEIGHT / 2;
bool CameraFirstMove = true;

Camera TheCamera;

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------


std::string FilePathVert = "Shader/Vertex_Shader.txt";
std::string FilePathFrag = "Shader/Fragment_Shader.txt";
std::string FilePathModel = "Models/Data Points";
std::string FilePathModel2 = "Models/Data Points Interpolation";
std::string FilePathModel3 = "Models/Data Points Vertex";

std::vector<FXGL::Line> LineModels;
std::vector<FXGL::Model> Models;
int main()
{
	FXGL::Model Cube;
    Cube.Vertices.emplace_back(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f);
    Cube.Vertices.emplace_back(0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f);
    Cube.Vertices.emplace_back(0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f);
    Cube.Vertices.emplace_back(-0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f);
    Cube.Indices.emplace_back(0);
    Cube.Indices.emplace_back(1);
    Cube.Indices.emplace_back(2);
    Cube.Indices.emplace_back(2);
    Cube.Indices.emplace_back(3);
    Cube.Indices.emplace_back(0);
    Cube.ModelPosition = glm::vec3(0.f, 0.f, -5.f);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_Button_Callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    FXGL::Shader TheShader;
    TheShader.set_ShaderPath(FilePathVert, FilePathFrag);
    TheShader.init_Shader();

    int modelLoc = glGetUniformLocation(TheShader.ShaderProgram, "model");
    int viewLoc = glGetUniformLocation(TheShader.ShaderProgram, "view");
    int projLoc = glGetUniformLocation(TheShader.ShaderProgram, "projection");

    FXGL::Line line1(true);
    line1.load_LineModel(FilePathModel);
    line1.set_Location(glm::vec3(10.f, 0.f, 0.f));
    FXGL::Line line2(true);
    line2.load_LineModel(FilePathModel2);
    FXGL::Line line3(false);
    line3.load_LineModel(FilePathModel3);
    LineModels.emplace_back(line1);
    LineModels.emplace_back(line2);
    LineModels.emplace_back(line3);
    Cube.bind_Buffer();
    Models.emplace_back(Cube);

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        DeltaTime = currentFrame - LastFrame;
        LastFrame = currentFrame;

        glm::mat4 Model_t;
		glm::mat4 View_t;
		glm::mat4 Projection_t;
        Model_t = glm::rotate(Cube.get_ModelMatrix(), glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));
        View_t = TheCamera.get_CameraView();
        Projection_t = glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH/SCR_HEIGHT), 0.1f, 100.0f);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Model_t));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(View_t));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(Projection_t));

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.f, 0.f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(TheShader.ShaderProgram);
        glLineWidth(5);
        glPointSize(5);

        for (auto model : LineModels)
        {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model.get_LineMatrix()));
            model.draw_Line();
        }
        for (auto model : Models)
        {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model.get_ModelMatrix()));
            model.draw_Model();
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        TheCamera.move_CameraSide(true);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        TheCamera.move_CameraSide(false);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        TheCamera.move_CameraFront(false);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        TheCamera.move_CameraFront(true);
    }
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

    TheCamera.update_CameraRotation(xOffset * 0.1f, yOffset * 0.1f);
}
