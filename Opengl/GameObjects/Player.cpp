#include "Player.h"

#include <iostream>

#include "../Engine/EngineManager.h"
#include "../Engine/Terrain.h"
#include "../Rendering/Renderer.h"
#include "../Engine/Input.h"
#include "Graphs.h"

void Player::game_Start()
{
	PlayerModel.init_Model();
	PlayerModel.set_ModelMesh(&Renderer::get()->Cube);

	SphereCollider.attach_ToGameObject(this);
	SphereCollider.set_SphereRadius(1.f);
	SphereCollider.enable_SphereVisible(true);

	BoxCollider.attach_ToGameObject(this);
	BoxCollider.set_BoxHeight(2.f);
	BoxCollider.set_BoxWidth(2.f);
	BoxCollider.set_BoxDepth(2.f);
	BoxCollider.enable_BoxVisible(true);

	PlayerCamera.attach_ToGameObject(this);
	PlayerCamera.update_CameraPosition(glm::vec3(0));
	PlayerCamera.set_CameraSpeed(50.f);
	EngineManager::TheEngineManager->add_ToCameraHandler(&PlayerCamera);
	FreeCamera.set_CameraSpeed(100.f);
	FreeCamera.set_CameraHeight(10.f);

	add_Tag("Player");
	int chunkXPos = static_cast<int>(floor(PlayerModel.get_WorldPosition().x / 30));
	int chunkZPos = static_cast<int>(floor(PlayerModel.get_WorldPosition().z / 30));
	ChunkPosition.x = chunkXPos;
	ChunkPosition.y = chunkZPos;
	Terrain::get_Terrain()->set_CurrentChunkPosition(ChunkPosition);
}

void Player::tick(float deltaTime)
{
	GameObject::tick(deltaTime);

	glm::ivec2 newChunkPosition(0);
	newChunkPosition.x = static_cast<int>(floor(PlayerModel.get_WorldPosition().x / 30));
	newChunkPosition.y = static_cast<int>(floor(PlayerModel.get_WorldPosition().z / 30));

	if (ChunkPosition.x != newChunkPosition.x || ChunkPosition.y != newChunkPosition.y)
	{
		Terrain::get_Terrain()->generate_RenderDistanceChunks(newChunkPosition-ChunkPosition);
		ChunkPosition = newChunkPosition;
	}

	for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
	{
		if (newChunkPosition == chunk.ChunkPosition)
		{
			//Terrain::get_Terrain()->generate_ChunksAroundChunk(chunk);
			EngineManager::TheEngineManager->TheTerrain = chunk.ChunkModel;
		}
	}


	glm::vec3 tempVec = PlayerCamera.get_CameraPosition();
	glm::vec3 tempVec2 = PlayerCamera.get_CameraTarget();
	tempVec2 *= 5;
	tempVec2.y = 0;
	tempVec.y -= 19;
	glm::vec3 tempVec3 = tempVec + tempVec2;
	
	PlayerModel.set_ModelPosition(tempVec+tempVec2);
	
	PlayerModel.rotate_Model(glm::vec3(0.f, -PlayerCamera.get_CameraRotation().x, 0.f));
	set_GameObjectPosition(tempVec+tempVec2);
	EngineManager::TheEngineManager->CharacterPoint = get_GameObjectPositionPtr();

	if (Input::key_Pressed(GLFW_KEY_1))
	{
		EngineManager::TheEngineManager->set_ActiveCamera(&PlayerCamera);
	}
	if (Input::key_Pressed(GLFW_KEY_2))
	{
		EngineManager::TheEngineManager->set_ActiveCamera(&FreeCamera);
	}
	if (Input::key_HeldDown(GLFW_KEY_D))
	{
		EngineManager::TheEngineManager->ActiveCamera->move_CameraSide(true);
	}
	if (Input::key_HeldDown(GLFW_KEY_A))
	{
		EngineManager::TheEngineManager->ActiveCamera->move_CameraSide(false);
	}
	if (Input::key_HeldDown(GLFW_KEY_S))
	{
		EngineManager::TheEngineManager->ActiveCamera->move_CameraFront(false);
	}
	if (Input::key_HeldDown(GLFW_KEY_W))
	{
		EngineManager::TheEngineManager->ActiveCamera->move_CameraFront(true);
	}
	if (Input::mouse_Pressed(GLFW_MOUSE_BUTTON_1))
	{
		spawn_Item();
	}
}


void Player::on_Collision(GameObject* otherGameObject)
{

}

glm::ivec2 Player::get_PlayerChunkPosition() const
{
	return ChunkPosition;
}

void Player::jump()
{
	Jumping = true;
}

void Player::spawn_Item()
{
	auto* spawnItem = new Graphs;
	//spawnItem->init_GameObject();
	glm::vec3 spawnItemPosition = get_GameObjectPosition();
	glm::vec3 forwardVector = glm::normalize(EngineManager::TheEngineManager->get_ActiveCamera().get_CameraTarget());
	forwardVector *= 2;
	spawnItem->set_GameObjectPosition(spawnItemPosition + forwardVector);

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
