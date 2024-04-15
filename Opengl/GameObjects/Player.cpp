#include "Player.h"

#include <iostream>

#include "../Engine/EngineManager.h"
#include "../Engine/Terrain.h"
#include "../Rendering/Renderer.h"

void Player::game_Start()
{
	PlayerModel.init_Model();
	PlayerModel.set_ModelMesh(&Renderer::get()->Cube);

	TheCamera.attach_ToGameObject(this);
	SphereCollider.attach_ToGameObject(this);
	SphereCollider.set_SphereRadius(1.f);
	SphereCollider.enable_SphereVisible(true);
	BoxCollider.attach_ToGameObject(this);
	BoxCollider.set_BoxHeight(2.f);
	BoxCollider.set_BoxWidth(2.f);
	BoxCollider.set_BoxDepth(2.f);
	BoxCollider.enable_BoxVisible(true);
	TheCamera.update_CameraPosition(glm::vec3(0));
	TheCamera.set_CameraSpeed(50.f);

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


	glm::vec3 tempVec = TheCamera.get_CameraPosition();
	glm::vec3 tempVec2 = TheCamera.get_CameraTarget();
	tempVec2 *= 5;
	tempVec2.y = 0;
	tempVec.y -= 19;
	glm::vec3 tempVec3 = tempVec + tempVec2;
	
	PlayerModel.set_ModelPosition(tempVec+tempVec2);
	
	PlayerModel.rotate_Model(glm::vec3(0.f, -TheCamera.get_CameraRotation().x, 0.f));
	set_GameObjectPosition(tempVec+tempVec2);
	EngineManager::TheEngineManager->CharacterPoint = get_GameObjectPositionPtr();
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
