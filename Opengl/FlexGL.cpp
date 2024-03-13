#include "FlexGL.h"

#include <ctime>

#include "EngineManager.h"

std::string FilePathModel = "Models/Data Points";
std::string FilePathModel3 = "Models/Data Points Vertex";

void FlexGL::game_Start(EngineManager* EM)
{
    Floor_1.init_Model();
    Wall_1.init_Model();
    Wall_2.init_Model();
    Wall_3.init_Model();
    Wall_4.init_Model();
    Wall_5.init_Model();
    Roof_1.init_Model();

    EM->TheCamera = &ThePlayer.TheCamera;
    create_Cube(Floor_1, glm::vec3(0.5f, 0.5f, 0.f));
    Floor_1.set_ModelPosition(glm::vec3(0.f, -20.f, 0.f));
    Floor_1.scale_Model(glm::vec3(50.f, 1.f, 50.f));

    create_Cube(Wall_1, glm::vec3(0.5f, 0.5f, 0.8f));
    create_Cube(Wall_2, glm::vec3(0.5f, 0.5f, 0.8f));
    create_Cube(Wall_3, glm::vec3(0.5f, 0.5f, 0.8f));
    create_Cube(Wall_4, glm::vec3(0.5f, 0.5f, 0.8f));
    create_Cube(Wall_5, glm::vec3(0.5f, 0.5f, 0.8f));
    Wall_1.set_ModelPosition(glm::vec3(0.f, -17.f, 0.f));
    Wall_1.scale_Model(glm::vec3(10.f, 6.f, 1.f));
    Wall_2.set_ModelPosition(glm::vec3(5.f, -17.f, 5.f));
    Wall_2.scale_Model(glm::vec3(1.f, 6.f, 11.f));
    Wall_3.set_ModelPosition(glm::vec3(-5.f, -17.f, 5.f));
    Wall_3.scale_Model(glm::vec3(1.f, 6.f, 11.f));
    Wall_4.set_ModelPosition(glm::vec3(-3.f, -17.f, 10.f));
    Wall_4.scale_Model(glm::vec3(4.f, 6.f, 1.f));
    Wall_5.set_ModelPosition(glm::vec3(3.f, -17.f, 10.f));
    Wall_5.scale_Model(glm::vec3(4.f, 6.f, 1.f));

    create_Cube(Roof_1, glm::vec3(0.8f, 0.5f, 0.5f));
    Roof_1.set_ModelPosition(glm::vec3(0.f, -13.5f, 5.f));
    Roof_1.scale_Model(glm::vec3(11.f, 1.f, 11.f));

    item_1.init_GameObject();
    item_2.init_GameObject();
    item_3.init_GameObject();
    item_4.init_GameObject();
    item_5.init_GameObject();
    item_6.init_GameObject();
    item_7.init_GameObject();
    item_8.init_GameObject();

    spawn_PickupRandom();

    graph_1.init_GameObject();
    ThePlayer.init_GameObject();
    TheNPC.init_GameObject();
    NPC_2.init_GameObject();
    NPC_2.enable_CircleDriving(true);
    NPC_3.init_GameObject();
    NPC_3.DoNothing = true;
    NPC_3.set_GameObjectVelocity(glm::vec3(0.f, 0.f, -1.f));
    glm::vec3 tempVec = box.get_GameObjectPosition();
    tempVec.x += 0.f;
    NPC_3.set_GameObjectPosition(glm::vec3(-40.f, 0.f, -25.f));
    TheDoor.init_GameObject();

    Camera_1.update_CameraPosition(glm::vec3(4.f, -14.f, 1.f));
    Camera_1.set_CameraSpeed(0.0f);

    camera.emplace_back(&ThePlayer.TheCamera);
    camera.emplace_back(&Camera_1);
    camera.emplace_back(&Camera_2);

    box.init_GameObject();
}

void FlexGL::tick(EngineManager* EM, float deltaTime)
{
	if (Scene_2 == true)
	{
       // EngineManager::TheEngineManager->TheCamera = camera[1];
        //EM->TheCamera = &Camera_1;
	}
	else
	{
        //EM->TheCamera = &ThePlayer.TheCamera;
	}
}

void FlexGL::Input(GLFWwindow* window)
{
	if (Scene_2 == false)
	{
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera[CameraIndex]->move_CameraSide(true);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera[CameraIndex]->move_CameraSide(false);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera[CameraIndex]->move_CameraFront(false);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera[CameraIndex]->move_CameraFront(true);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            ThePlayer.jump();
        }
	}

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		if (Scene_2 == false)
		{
            Scene_2 = true;
		}
		else
		{
            Scene_2 = false;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (KeyPressed == false)
		{
            CameraIndex += 1;
            if (CameraIndex >= camera.size())
            {
                CameraIndex = 0;
            }
            EngineManager::TheEngineManager->TheCamera = camera[CameraIndex];
		}

        KeyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
        KeyPressed = false;
	}
}

void FlexGL::spawn_PickupRandom()
{
    srand(time(NULL));
    int xDistance = 25.f;
    int yDistance = -19.f;
    int zDistance = 25.f;
    item_1.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
    item_2.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
    item_3.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
    item_4.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
    item_5.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
    item_6.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
    item_7.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
    item_8.set_GameObjectPosition(glm::vec3((rand() % xDistance*2) - xDistance, yDistance, (rand() % zDistance*2) - zDistance));
}
