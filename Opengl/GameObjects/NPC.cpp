#include "NPC.h"

#include "../Engine/EngineManager.h"
#include "../Rendering/Renderer.h"

void NPC::game_Start()
{
	NPCModel.init_Model();
	NPCModel.set_ModelMesh(&Renderer::get()->Cube);
	NPCModel.bind_ToGameObject(this);
	NPCModel.set_ModelPosition(glm::vec3(0.f));

	BoxCollider.attach_ToGameObject(this);
	BoxCollider.enable_BoxVisible(true);
	BoxCollider.set_BoxWidth(1.1f);
	BoxCollider.set_BoxHeight(1.1f);
	BoxCollider.set_BoxDepth(1.1f);
}

void NPC::tick(float deltaTime)
{
	GameObject::tick(deltaTime);

	if (OriginalePath == false)
	{
		move_UpDown();
		return;
	}

	if (DoNothing == false)
	{
		if (CircleDriving == true)
		{
			calculate_CirclePath(deltaTime);
		}
		else
		{
			move_NPC(deltaTime);
		}
	}

	//calculate_Height();
	find_Height();
}

void NPC::enable_CircleDriving(bool enable)
{
	CircleDriving = enable;
}

void NPC::move_UpDown()
{
	if (get_GameObjectPosition().y >= 25.f)
	{
		set_GameObjectVelocity(glm::vec3(0.f, -10.f, 0.f));
	}
	if (get_GameObjectPosition().y <= -25.f)
	{
		set_GameObjectVelocity(glm::vec3(0.f, 10.f, 0.f));
	}
}

void NPC::switch_Path()
{
	if (OriginalePath == true)
	{
		OriginalePath = false;
		set_GameObjectVelocity(glm::vec3(0.f, 10.f, 0.f));
	}
	else
	{
		OriginalePath = true;
		set_GameObjectVelocity(glm::vec3(0.f, 0.f, 0.f));
	}
}

void NPC::move_NPC(float deltaTime)
{
	if (xPos > 25.f || xPos < -25.f)
	{
		xDirection *= -1.f;
	}
	
	xPos += NPCSpeed * deltaTime * xDirection;
	set_GameObjectPosition(glm::vec3(xPos, -19.f, calculate_NPCPath(xPos)));
}

float NPC::calculate_NPCPath(float x)
{
	return (x*x*x)*0.01f;
}

void NPC::calculate_CirclePath(float deltaTime)
{
	set_GameObjectPosition(glm::vec3(Radius * sin(glm::radians(Degrees)), -19.f, Radius * cos(glm::radians(Degrees))));
	Degrees += 45.f * deltaTime;
	Radius += 5.f * SmallerBigger *deltaTime;
	if (Degrees >= 360.f)
	{
		Degrees = 0.f;
	}
	if (Radius >= 50.f || Radius <= 15.f)
	{
		SmallerBigger *= -1;
	}
}

void NPC::calculate_Height()
{
	glm::ivec2 itemChunkPosition;
	itemChunkPosition.x = static_cast<int32_t>(floor(get_GameObjectPosition().x / 30));
	itemChunkPosition.y = static_cast<int32_t>(floor(get_GameObjectPosition().z / 30));

	for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
	{
		if (chunk.ChunkPosition == itemChunkPosition)
		{
			for (const Triangle& triangle : chunk.ChunkModel->ModelMesh->Triangles)
			{
				if (EngineManager::calculate_PointOnTriangle(get_GameObjectPosition(),
					chunk.ChunkModel->ModelMesh->Vertices[triangle.FirstIndex].Position,
					chunk.ChunkModel->ModelMesh->Vertices[triangle.SecondIndex].Position,
					chunk.ChunkModel->ModelMesh->Vertices[triangle.ThirdIndex].Position,
					chunk.ChunkModel->get_WorldPosition()))
				{
					get_GameObjectPosition().y += 0.5f;
					break;
				}
			}
			break;
		}
	}
}

bool NPC::find_Height()
{
	glm::ivec2 itemChunkPosition;
	itemChunkPosition.x = static_cast<int32_t>(floor(get_GameObjectPosition().x / 30));
	itemChunkPosition.y = static_cast<int32_t>(floor(get_GameObjectPosition().z / 30));

	float xPosition = itemChunkPosition.x * 30;
	float yPosition = itemChunkPosition.y * 30;

	float playerXPosition = floor(get_GameObjectPosition().x);
	float playerZPosition = floor(get_GameObjectPosition().z);
	glm::vec3 tempVec = get_GameObjectPosition();

	float xIndex = xPosition - playerXPosition;
	float yIndex = yPosition - playerZPosition;
	xIndex *= -1;
	yIndex *= -1;

	int index = (xIndex * 31) + yIndex;
	int index2 = ((xIndex + 1) * 31) + yIndex;

	Chunk* tempChunkPtr = nullptr;

	for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
	{
		if (chunk.ChunkPosition == itemChunkPosition)
		{
			tempChunkPtr = &chunk;
			break;
		}
	}

	if (tempChunkPtr == nullptr)
	{
		return false;
	}

	Vertex v1 = tempChunkPtr->ChunkModel->ModelMesh->Vertices[index];
	Vertex v2 = tempChunkPtr->ChunkModel->ModelMesh->Vertices[index2];
	Vertex v3 = tempChunkPtr->ChunkModel->ModelMesh->Vertices[index2 + 1];
	Vertex v4 = tempChunkPtr->ChunkModel->ModelMesh->Vertices[index + 1];

	if (EngineManager::calculate_PointOnTriangle(tempVec, v1.Position,
		v2.Position, v3.Position,
		tempChunkPtr->ChunkModel->get_WorldPosition()))
	{

	}
	if (EngineManager::calculate_PointOnTriangle(tempVec, v3.Position,
		v4.Position, v1.Position,
		tempChunkPtr->ChunkModel->get_WorldPosition()))
	{
	}

	tempVec.y += 0.5f;

	set_GameObjectPosition(tempVec);

	return true;
}

