#include "FlexGL.h"

#include "EngineManager.h"

std::string FilePathModel = "Models/Data Points";
std::string FilePathModel2 = "Models/Data Points Interpolation";
std::string FilePathModel3 = "Models/Data Points Vertex";

void FlexGL::game_Start(EngineManager* EM)
{
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
    Cube.bind_Buffer();
    EM->ModelHandler.emplace_back(&Cube);

    line1.load_LineModel(FilePathModel);
    line1.set_Location(glm::vec3(10.f, 0.f, 0.f));
    line2.load_LineModel(FilePathModel2);
    line3.load_LineModel(FilePathModel3);
    EM->LineModelHandler.emplace_back(&line1);
    EM->LineModelHandler.emplace_back(&line2);
    EM->LineModelHandler.emplace_back(&line3);

    EM->TheCamera = &Camera_1;
}

void FlexGL::tick(EngineManager* EM, float deltaTime)
{
}

void FlexGL::Input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Camera_1.move_CameraSide(true);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Camera_1.move_CameraSide(false);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Camera_1.move_CameraFront(false);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Camera_1.move_CameraFront(true);
    }
}
