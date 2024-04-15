#include "FlexGL.h"

#include <ctime>

#include "EngineManager.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Renderer.h"
#include "../Engine/Input.h"

std::string FilePathModel = "Models/Data Points";
std::string FilePathModel2 = "Models/Function Points";
std::string FilePathModel3 = "Models/Data Points Vertex";
std::string FilePathModel4 = "Models/PerlinNoise";

void FlexGL::game_Start()
{
    //Floor_1.init_Model();
    //Wall_1.init_Model();
    //Wall_2.init_Model();
    //Wall_3.init_Model();
    //Wall_4.init_Model();
    //Wall_5.init_Model();
    //Roof_1.init_Model();

    Terrain::get_Terrain()->generate_Chunk(glm::ivec2(0));
    Terrain::get_Terrain()->generate_ChunksAroundChunk(Terrain::get_Terrain()->Chunks[0]);

    TerrainLine.init_Model();
    TerrainLine.set_ModelMesh(&Renderer::get()->Line);
    TerrainLine.set_ModelPosition(glm::vec3(0.f));
    create_LinesOnTerrain(*TerrainLine.ModelMesh, -10.f, 10.f, 0.1f);
    TerrainLine.turn_OnLine();

    EngineManager::TheEngineManager->ActiveCamera = &ThePlayer.TheCamera;

    //create_Cube(Floor_1, glm::vec3(0.5f, 0.5f, 0.f));
    //Floor_1.set_ModelPosition(glm::vec3(0.f, -20.f, 0.f));
    //Floor_1.scale_Model(glm::vec3(50.f, 1.f, 50.f));

    //create_Cube(Wall_1, glm::vec3(0.5f, 0.5f, 0.8f));
    //create_Cube(Wall_2, glm::vec3(0.5f, 0.5f, 0.8f));
    //create_Cube(Wall_3, glm::vec3(0.5f, 0.5f, 0.8f));
    //create_Cube(Wall_4, glm::vec3(0.5f, 0.5f, 0.8f));
    //create_Cube(Wall_5, glm::vec3(0.5f, 0.5f, 0.8f));
    //Wall_1.set_ModelPosition(glm::vec3(0.f, -17.f, 0.f));
    //Wall_1.scale_Model(glm::vec3(10.f, 6.f, 1.f));
    //Wall_2.set_ModelPosition(glm::vec3(5.f, -17.f, 5.f));
    //Wall_2.scale_Model(glm::vec3(1.f, 6.f, 11.f));
    //Wall_3.set_ModelPosition(glm::vec3(-5.f, -17.f, 5.f));
    //Wall_3.scale_Model(glm::vec3(1.f, 6.f, 11.f));
    //Wall_4.set_ModelPosition(glm::vec3(-3.f, -17.f, 10.f));
    //Wall_4.scale_Model(glm::vec3(4.f, 6.f, 1.f));
    //Wall_5.set_ModelPosition(glm::vec3(3.f, -17.f, 10.f));
    //Wall_5.scale_Model(glm::vec3(4.f, 6.f, 1.f));

    //create_Cube(Roof_1, glm::vec3(0.8f, 0.5f, 0.5f));
    //Roof_1.set_ModelPosition(glm::vec3(0.f, -13.5f, 5.f));
    //Roof_1.scale_Model(glm::vec3(11.f, 1.f, 11.f));
	//TheDoor.init_GameObject();

    graph_1.init_GameObject();
    ThePlayer.init_GameObject();
    TheNPC.init_GameObject();
    NPC_2.init_GameObject();
    NPC_2.enable_CircleDriving(true);
    NPC_3.init_GameObject();
    NPC_3.DoNothing = true;
    NPC_3.set_GameObjectVelocity(glm::vec3(0.f, 0.f, -1.f));
    NPC_3.set_GameObjectPosition(glm::vec3(-40.f, 0.f, -25.f));

    Camera_1.update_CameraPosition(glm::vec3(4.f, -14.f, 1.f));
    Camera_1.set_CameraSpeed(0.0f);
    Camera_1.turn_CameraAround();
    Camera_2.update_CameraPosition(glm::vec3(-4.f, -14.f, 1.f));
    Camera_2.set_CameraSpeed(0.0f);
    Camera_2.turn_CameraAround();

	Cameras.emplace_back(&ThePlayer.TheCamera);
    Cameras.emplace_back(&Camera_1);

    EngineManager::TheEngineManager->TheTerrain = Terrain::get_Terrain()->Chunks[0].ChunkModel;

    spawn_PickupRandom();
}

void FlexGL::tick(float deltaTime)
{
    //std::cout << ThePlayer.get_GameObjectPosition().x << ThePlayer.get_GameObjectPosition().y << ThePlayer.get_GameObjectPosition().z << std::endl;
	if (EngineManager::TheEngineManager->Scene_2 == true && CameraIs1 == true)
	{
        EngineManager::TheEngineManager->set_ActiveCamera(&Camera_1);
	}
    if (Input::FKey == true)
    {
        spawn_Item();
    }
}

void FlexGL::input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        ThePlayer.TheCamera.move_CameraSide(true);
       
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        ThePlayer.TheCamera.move_CameraSide(false);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        ThePlayer.TheCamera.move_CameraFront(false);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        ThePlayer.TheCamera.move_CameraFront(true);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        ThePlayer.jump();
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (KeyPressed == false)
		{
			
            if (DebugTurnedOff == true)
            {
                EngineManager::TheEngineManager->turnOff_DebugMode(true);
                DebugTurnedOff = false;
                //TheNPC.switch_Path();
                //NPC_2.switch_Path();
            }
            else
            {
                EngineManager::TheEngineManager->turnOff_DebugMode(false);
                DebugTurnedOff = true;
                //TheNPC.switch_Path();
                //NPC_2.switch_Path();
            }
            
		}

        KeyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
        KeyPressed = false;
	}

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        if (KeyPressed2 == false)
        {
            if (EngineManager::TheEngineManager->Scene_2 == true && CameraIs1 == true)
            {
                EngineManager::TheEngineManager->set_ActiveCamera(&Camera_2);
                CameraIs1 = false;
            }
            else if (EngineManager::TheEngineManager->Scene_2 == true && CameraIs1 == false)
            {
                EngineManager::TheEngineManager->set_ActiveCamera(&Camera_1);
                CameraIs1 = true;
            }
        }

        KeyPressed2 = true;
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_RELEASE)
    {
        KeyPressed2 = false;
    }
}

void FlexGL::spawn_PickupRandom()
{
    srand(time(NULL));
    int xDistance = 25.f;
    int yDistance = 0.f;
    int zDistance = 25.f;
    int numberOfItems = 8;
    float tempXPos = 0.f;
    float tempZPos = 0.f;

    items.reserve(numberOfItems);

    for (int i = 0; i < numberOfItems; i++)
    {
        tempXPos = (rand() % xDistance * 2) - xDistance;
        tempZPos = (rand() % zDistance * 2) - zDistance;

        PickUpItem* tempItem = new PickUpItem;
        tempItem->init_GameObject();
        tempItem->set_GameObjectPosition(glm::vec3(tempXPos, yDistance, tempZPos));

        glm::ivec2 itemChunkPosition;
        itemChunkPosition.x = static_cast<int32_t>(floor(tempXPos / 30));
        itemChunkPosition.y = static_cast<int32_t>(floor(tempZPos / 30));

        for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
        {
            if (itemChunkPosition == chunk.ChunkPosition)
            {
                for (const Triangle& triangle : chunk.ChunkModel->ModelMesh->Triangles)
                {
                    if (EngineManager::calculate_PointOnTriangle(tempItem->get_GameObjectPosition(),
                        chunk.ChunkModel->ModelMesh->Vertices[triangle.FirstIndex].Position,
                        chunk.ChunkModel->ModelMesh->Vertices[triangle.SecondIndex].Position,
                        chunk.ChunkModel->ModelMesh->Vertices[triangle.ThirdIndex].Position,
                        chunk.ChunkModel->get_WorldPosition()))
                    {
                        tempItem->get_GameObjectPosition().y += 0.5f;
                        break;
                    }
                }
                break;
            }
        }


        items.emplace_back(tempItem);
    }
}

void FlexGL::spawn_Item()
{
    Graphs* spawnItem = new Graphs;
    spawnItem->init_GameObject();
    glm::vec3 spawnItemPosition = ThePlayer.get_GameObjectPosition();
    glm::vec3 forwardVector = glm::normalize(EngineManager::TheEngineManager->get_ActiveCamera().get_CameraTarget());
    forwardVector *= 2;
    spawnItem->set_GameObjectPosition(spawnItemPosition+forwardVector);

    std::cout << spawnItem->get_GameObjectPosition().x << " " << spawnItem->get_GameObjectPosition().y
        << " " << spawnItem->get_GameObjectPosition().z << std::endl;

    glm::ivec2 itemChunkPosition;
    itemChunkPosition.x = static_cast<int32_t>(floor(spawnItem->get_GameObjectPosition().x / 30));
    itemChunkPosition.y = static_cast<int32_t>(floor(spawnItem->get_GameObjectPosition().z / 30));

    for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
    {
	    if (chunk.ChunkPosition == itemChunkPosition)
	    {
            for (const Triangle& triangle : chunk.ChunkModel->ModelMesh->Triangles)
            {
                if (EngineManager::calculate_PointOnTriangle(spawnItem->get_GameObjectPosition(), 
                    chunk.ChunkModel->ModelMesh->Vertices[triangle.FirstIndex].Position,
                    chunk.ChunkModel->ModelMesh->Vertices[triangle.SecondIndex].Position,
                    chunk.ChunkModel->ModelMesh->Vertices[triangle.ThirdIndex].Position,
                    chunk.ChunkModel->get_WorldPosition()))
                {
                    spawnItem->get_GameObjectPosition().y += 0.5f;
                    break;
                }
            }
            break;
	    }
    }
    spawnItem->game_Start();
}
