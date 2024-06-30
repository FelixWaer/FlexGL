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
    Terrain::get_Terrain()->generate_Chunk(glm::ivec2(0));
    Terrain::get_Terrain()->generate_ChunksAroundChunk(Terrain::get_Terrain()->Chunks[0]);

    TerrainLine.init_Model();
    TerrainLine.set_ModelMesh(&Renderer::get()->Line);
    TerrainLine.set_ModelPosition(glm::vec3(0.f));
    create_LinesOnTerrain(*TerrainLine.ModelMesh, -10.f, 10.f, 0.1f);
    TerrainLine.turn_OnLine();

    EngineManager::get_Engine()->ActiveCamera = &ThePlayer.PlayerCamera;


    SkyBox.init_Model();
    SkyBox.set_ModelMesh(&Renderer::get()->Cube);
    SkyBox.set_ModelTexture(&Renderer::get()->SkyboxTexture);
    SkyBox.skybox = true;
    EngineManager::get_Engine()->set_Skybox(&SkyBox);

    graph_1.init_GameObject();
    ThePlayer.init_GameObject();
    TheNPC.init_GameObject();
    NPC_2.init_GameObject();
    NPC_2.enable_CircleDriving(true);
    NPC_3.init_GameObject();
    NPC_3.DoNothing = true;
    NPC_3.set_GameObjectVelocity(glm::vec3(0.f, 0.f, -1.f));
    NPC_3.set_GameObjectPosition(glm::vec3(-40.f, 0.f, -25.f));

	Cameras.emplace_back(&ThePlayer.PlayerCamera);
    Cameras.emplace_back(&ThePlayer.FreeCamera);

    EngineManager::get_Engine()->TheTerrain = Terrain::get_Terrain()->Chunks[0].ChunkModel;

    spawn_PickupRandom();
}

void FlexGL::tick(float deltaTime)
{

}

void FlexGL::input(GLFWwindow* window)
{

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
                EngineManager::get_Engine()->turnOff_DebugMode(true);
                DebugTurnedOff = false;
                //TheNPC.switch_Path();
                //NPC_2.switch_Path();
            }
            else
            {
                EngineManager::get_Engine()->turnOff_DebugMode(false);
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
