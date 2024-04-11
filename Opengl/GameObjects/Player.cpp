#include "Player.h"

#include <iostream>

#include "../Engine/EngineManager.h"
#include "../Engine/Terrain.h"

void Player::game_Start()
{
	PlayerModel.init_Model();
	create_Cube(PlayerModel, glm::vec3(0.f, 0.f, 1.f));


	TheCamera.attach_ToGameObject(this);
	SphereCollider.attach_ToGameObject(this);
	SphereCollider.set_SphereRadius(1.f);
	SphereCollider.enable_SphereVisible(true);
	BoxCollider.attach_ToGameObject(this);
	BoxCollider.set_BoxHeight(2.f);
	BoxCollider.set_BoxWidth(2.f);
	BoxCollider.set_BoxDepth(2.f);
	BoxCollider.enable_BoxVisible(true);
	TheCamera.update_CameraPosition(glm::vec3(-4.f, -20.f, 40.f));
	TheCamera.set_CameraSpeed(50.f);

	add_Tag("Player");
}

void Player::tick(float deltaTime)
{
	GameObject::tick(deltaTime);

	int32_t chunkXPos = static_cast<int32_t>(floor(PlayerModel.get_WorldPosition().x / 30));
	int32_t chunkYPos = static_cast<int32_t>(floor(PlayerModel.get_WorldPosition().z / 30));
	std::cout << chunkXPos << " " << chunkYPos << std::endl;

	for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
	{
		if (chunkXPos == chunk.xPos && chunkYPos == chunk.yPos)
		{
			EngineManager::TheEngineManager->TheTerrain = chunk.ChunkModel;
		}
	}

	//if (Jumping == true)
	//{
	//	TheCamera.move_CameraUp(20.f * deltaTime);
	//	Jumping = false;
	//}
	//else
	//{
	//	if (TheCamera.get_CameraPosition().y < -16.f)
	//	{
	//		TheCamera.set_CameraHeight(-16.f);
	//	}
	//	TheCamera.move_CameraUp(-5.f * deltaTime);
	//}
	//TheCamera.lock_CameraPitch(-10.f);
	glm::vec3 tempVec = TheCamera.get_CameraPosition();
	glm::vec3 tempVec2 = TheCamera.get_CameraTarget();
	tempVec2 *= 5;
	tempVec2.y = 0;
	tempVec.y -= 2;
	glm::vec3 tempVec3 = tempVec + tempVec2;
	
	PlayerModel.set_ModelPosition(tempVec+tempVec2);
	
	PlayerModel.rotate_Model(glm::vec3(0.f, -TheCamera.get_CameraRotation().x, 0.f));
	set_GameObjectPosition(tempVec+tempVec2);
	EngineManager::TheEngineManager->CharacterPoint = get_GameObjectPositionPtr();
}

void Player::on_Collision(GameObject* otherGameObject)
{

}

void Player::jump()
{
	Jumping = true;
}
