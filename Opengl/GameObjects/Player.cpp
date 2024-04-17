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
	PlayerModel.bind_ToGameObject(this);

	SphereCollider.attach_ToGameObject(this);
	SphereCollider.set_SphereRadius(1.f);
	SphereCollider.enable_SphereVisible(true);

	BoxCollider.attach_ToGameObject(this);
	BoxCollider.set_BoxHeight(2.f);
	BoxCollider.set_BoxWidth(2.f);
	BoxCollider.set_BoxDepth(2.f);
	BoxCollider.enable_BoxVisible(true);

	PlayerCamera.attach_ToGameObject(this);
	PlayerCamera.update_CameraPosition(glm::vec3(10.f, 0.f, 10.f));
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
		glm::vec3 normal = glm::normalize(glm::cross(get_GameObjectFront(), glm::vec3(0.f, 1.f, 0.f)));
		set_GameObjectVelocity((normal *= 100.f));
	}
	if (Input::key_HeldDown(GLFW_KEY_A))
	{
		glm::vec3 normal = glm::normalize(glm::cross(get_GameObjectFront(), glm::vec3(0.f, 1.f, 0.f)));
		set_GameObjectVelocity(-(normal *= 100.f));
	}
	if (Input::key_HeldDown(GLFW_KEY_S))
	{
		glm::vec3 normal = glm::normalize(get_GameObjectFront());
		set_GameObjectVelocity(-(normal *= 100.f));
	}
	if (Input::key_HeldDown(GLFW_KEY_W))
	{
		glm::vec3 normal = glm::normalize(get_GameObjectFront());
		set_GameObjectVelocity(normal*=100.f);
	}
	if (Input::mouse_Pressed(GLFW_MOUSE_BUTTON_1))
	{
		spawn_Item();
	}

	EngineManager::TheEngineManager->CharacterPoint = get_GameObjectPositionPtr();

	glm::ivec2 newChunkPosition(0);
	newChunkPosition.x = static_cast<int>(floor(PlayerModel.get_WorldPosition().x / 30));
	newChunkPosition.y = static_cast<int>(floor(PlayerModel.get_WorldPosition().z / 30));

	if (ChunkPosition.x != newChunkPosition.x || ChunkPosition.y != newChunkPosition.y)
	{
		Terrain::get_Terrain()->generate_RenderDistanceChunks(newChunkPosition - ChunkPosition);
		ChunkPosition = newChunkPosition;
		for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
		{
			if (newChunkPosition == chunk.ChunkPosition)
			{
				EngineManager::TheEngineManager->TheTerrain = chunk.ChunkModel;
			}
		}
	}

	//find_Height();
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

bool Player::find_Height()
{
	if (EngineManager::TheEngineManager->TheTerrain != nullptr)
	{

		float xPosition = ChunkPosition.x * 30;
		float yPosition = ChunkPosition.y * 30;
		float playerXPosition = floor(get_GameObjectPosition().x);
		float playerZPosition = floor(get_GameObjectPosition().z);

		float xIndex = playerXPosition - xPosition;
		float yIndex = playerZPosition - yPosition;

		if (xPosition < 0)
		{
			xPosition *= -1;
			playerXPosition *= -1;
			xIndex = xPosition - playerXPosition;
		}
		if (yPosition < 0)
		{
			yPosition *= -1;
			playerZPosition *= -1;
			xIndex = yPosition - playerZPosition;
		}

		Vertex v1 = EngineManager::TheEngineManager->TheTerrain->ModelMesh->Vertices[(xIndex * 30)+yIndex];
		Vertex v2 = EngineManager::TheEngineManager->TheTerrain->ModelMesh->Vertices[((xIndex+1) * 30) + yIndex];
		Vertex v3 = EngineManager::TheEngineManager->TheTerrain->ModelMesh->Vertices[(((xIndex + 1) * 30) + yIndex) + 1];
		Vertex v4 = EngineManager::TheEngineManager->TheTerrain->ModelMesh->Vertices[((xIndex * 30) + yIndex)+1];

		if (EngineManager::calculate_PointOnTriangle(get_GameObjectPosition(), v1.Position,
			v2.Position, v3.Position,
			EngineManager::TheEngineManager->TheTerrain->get_WorldPosition()))
		{
			std::cout << " sds" << std::endl;
			PlayerCamera.get_CameraPosition().y = get_GameObjectPosition().y + 5;
		}
		if (EngineManager::calculate_PointOnTriangle(get_GameObjectPosition(), v3.Position,
			v4.Position, v1.Position,
			EngineManager::TheEngineManager->TheTerrain->get_WorldPosition()))
		{
			std::cout << " sds" << std::endl;
			PlayerCamera.get_CameraPosition().y = get_GameObjectPosition().y + 5;
		}
	}
	return true;
}
