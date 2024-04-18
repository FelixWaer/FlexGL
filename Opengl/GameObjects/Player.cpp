#include "Player.h"

#include <iostream>
#include <windows.h>

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
	EngineManager::get_Engine()->add_ToCameraHandler(&PlayerCamera);
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
		EngineManager::get_Engine()->set_ActiveCamera(&PlayerCamera);
	}
	if (Input::key_Pressed(GLFW_KEY_2))
	{
		EngineManager::get_Engine()->set_ActiveCamera(&FreeCamera);
	}
	if (Input::key_HeldDown(GLFW_KEY_D))
	{
		glm::vec3 normal = glm::normalize(glm::cross(get_GameObjectFront(), glm::vec3(0.f, 1.f, 0.f)));
		set_GameObjectVelocity((normal *= MovementSpeed));
	}
	if (Input::key_HeldDown(GLFW_KEY_A))
	{
		glm::vec3 normal = glm::normalize(glm::cross(get_GameObjectFront(), glm::vec3(0.f, 1.f, 0.f)));
		set_GameObjectVelocity(-(normal *= MovementSpeed));
	}
	if (Input::key_HeldDown(GLFW_KEY_S))
	{
		glm::vec3 normal = glm::normalize(get_GameObjectFront());
		set_GameObjectVelocity(-(normal *= MovementSpeed));
	}
	if (Input::key_HeldDown(GLFW_KEY_W))
	{
		glm::vec3 normal = glm::normalize(get_GameObjectFront());
		set_GameObjectVelocity(normal*= MovementSpeed);
	}
	if (Input::key_Pressed(GLFW_KEY_SPACE))
	{
		if (Jumping == false)
		{
			Jumping = true;
		}
	}
	if (Input::key_HeldDown(GLFW_KEY_LEFT_SHIFT))
	{
		MovementSpeed = 50.f;
	}
	else
	{
		MovementSpeed = 20.f;
	}

	if (Input::mouse_Pressed(GLFW_MOUSE_BUTTON_1))
	{
		if (CanMine == true)
		{
			mine();
			CanMine = false;
		}
	}
	if (Input::mouse_HeldDown(GLFW_MOUSE_BUTTON_1))
	{
		if (CanMine == true)
		{
			mine();
			CanMine = false;
		}
	}
	if (Input::mouse_Pressed(GLFW_MOUSE_BUTTON_2))
	{
		spawn_Item();
	}

	if (MineTimer >= 1.f )
	{
		MineTimer = 0.f;
		CanMine = true;
	}

	if (CanMine == false)
	{
		MineTimer += deltaTime;
	}

	if (falling == true)
	{
		set_GameObjectVelocity(glm::vec3(0.f, -50.f, 0.f));
	}

	jump(deltaTime);
	EngineManager::get_Engine()->CharacterPoint = get_GameObjectPositionPtr();

	glm::ivec2 newChunkPosition(0);
	newChunkPosition.x = static_cast<int>(floor(PlayerModel.get_WorldPosition().x / 30));
	newChunkPosition.y = static_cast<int>(floor(PlayerModel.get_WorldPosition().z / 30));

	if (ChunkPosition.x != newChunkPosition.x || ChunkPosition.y != newChunkPosition.y)
	{
		for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
		{
			if (newChunkPosition == chunk.ChunkPosition)
			{
				EngineManager::get_Engine()->TheTerrain = chunk.ChunkModel;
				Terrain::get_Terrain()->generate_RenderDistanceChunks(newChunkPosition - ChunkPosition, chunk);
			}
		}
		ChunkPosition = newChunkPosition;
	}

	calculate_Height();
	//find_Height();
}


void Player::on_Collision(GameObject* otherGameObject)
{

}

glm::ivec2 Player::get_PlayerChunkPosition() const
{
	return ChunkPosition;
}

void Player::jump(float deltaTime)
{
	if (Jumping == true)
	{
		set_GameObjectVelocity(glm::vec3(0.f, JumpSpeed, 0.f));
		JumpSpeed -= 40.f * deltaTime;
		return;
	}
	JumpSpeed = 100.f;
}

void Player::spawn_Item()
{
	Graphs* spawnItem = new Graphs;
	spawnItem->init_GameObject();
	glm::vec3 spawnItemPosition = get_GameObjectPosition();
	glm::vec3 forwardVector = glm::normalize(EngineManager::get_Engine()->get_ActiveCamera().get_CameraTarget());
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
	if (EngineManager::get_Engine()->TheTerrain != nullptr)
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

		Vertex v1 = EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[(xIndex * 30)+yIndex];
		Vertex v2 = EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[((xIndex+1) * 30) + yIndex];
		Vertex v3 = EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[(((xIndex + 1) * 30) + yIndex) + 1];
		Vertex v4 = EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[((xIndex * 30) + yIndex)+1];

		if (EngineManager::calculate_PointOnTriangle(get_GameObjectPosition(), v1.Position,
			v2.Position, v3.Position,
			EngineManager::get_Engine()->TheTerrain->get_WorldPosition()))
		{
			std::cout << " sds" << std::endl;
			PlayerCamera.get_CameraPosition().y = get_GameObjectPosition().y + 5;
		}
		if (EngineManager::calculate_PointOnTriangle(get_GameObjectPosition(), v3.Position,
			v4.Position, v1.Position,
			EngineManager::get_Engine()->TheTerrain->get_WorldPosition()))
		{
			PlayerCamera.get_CameraPosition().y = get_GameObjectPosition().y + 5;
		}
	}
	return true;
}

void Player::calculate_Height()
{
	if (EngineManager::get_Engine()->TheTerrain == nullptr)
	{
		return;
	}

	glm::vec3 tempVec = get_GameObjectPosition();
	for (const Triangle& triangle : EngineManager::get_Engine()->TheTerrain->ModelMesh->Triangles)
	{
		if (EngineManager::calculate_PointOnTriangle(tempVec, EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[triangle.FirstIndex].Position,
			EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[triangle.SecondIndex].Position,
			EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[triangle.ThirdIndex].Position,
			EngineManager::get_Engine()->TheTerrain->get_WorldPosition()))
		{
			tempVec.y += 0.5f;
			if (get_GameObjectPosition().y > tempVec.y)
			{
				falling = true;
			}
			else
			{
				get_GameObjectPosition().y = tempVec.y;
				if (falling == true)
				{
					Jumping = false;
				}
				falling = false;
			}
		}
	}
}

void Player::mine()
{
	if (EngineManager::get_Engine()->TheTerrain == nullptr)
	{
		return;
	}
	Mesh* modelMesh = EngineManager::get_Engine()->TheTerrain->ModelMesh;
	for (size_t i = 0; i < modelMesh->Triangles.size(); i++)
	{
		if (EngineManager::calculate_PointOnTriangle(get_GameObjectPosition(),
			modelMesh->Vertices[modelMesh->Triangles[i].FirstIndex].Position,
			modelMesh->Vertices[modelMesh->Triangles[i].SecondIndex].Position,
			modelMesh->Vertices[modelMesh->Triangles[i].ThirdIndex].Position,
			EngineManager::get_Engine()->TheTerrain->get_WorldPosition()))
		{
			if (i % 2 == 0)
			{
				
			}
			get_GameObjectPosition().y += 0.5f;

			uint64_t index = modelMesh->Triangles[i].ThirdIndex;
			uint64_t indexNumber = index / 31;

			EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[index].Position.y -= 2.f;

			if (index % 31 != 30)
			{
				std::cout << "1" << std::endl;
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[index + 1].Position.y -= 1.f;
			}
			if (index % 31 != 0)
			{
				std::cout << "2" << std::endl;
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[index - 1].Position.y -= 1.f;
			}
			if (indexNumber != 0)
			{
				std::cout << "3" << std::endl;
				uint64_t tempInt = index - ((indexNumber - 1) * 31);
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[tempInt].Position.y -= 1.f;
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[tempInt + 1].Position.y -= 0.5f;
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[tempInt - 1].Position.y -= 0.5f;
			}
			if (indexNumber != 30)
			{
				std::cout << "4" << std::endl;
				uint64_t tempInt = index - ((indexNumber - 1) * 31);
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[tempInt].Position.y -= 1.f;
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[tempInt + 1].Position.y -= 0.5f;
				EngineManager::get_Engine()->TheTerrain->ModelMesh->Vertices[tempInt - 1].Position.y -= 0.5f;
			}


			EngineManager::get_Engine()->TheTerrain->ModelMesh->bind_Buffer();
		}
	}
}
