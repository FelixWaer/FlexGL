#include "Player.h"

#include <iostream>

#include "../EngineManager.h"

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
	TheCamera.update_CameraPosition(glm::vec3(0.f, -14.f, 25.f));
	TheCamera.set_CameraSpeed(0.1f);

	add_Tag("Player");
}

void Player::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
	if (Jumping == true)
	{
		TheCamera.move_CameraUp(20.f * deltaTime);
		Jumping = false;
	}
	else
	{
		if (TheCamera.get_CameraPosition().y < -16.f)
		{
			TheCamera.set_CameraHeight(-16.f);
		}
		TheCamera.move_CameraUp(-5.f * deltaTime);
	}
	TheCamera.lock_CameraPitch(-10.f);
	glm::vec3 tempVec = TheCamera.get_CameraPosition();
	glm::vec3 tempVec2 = TheCamera.get_CameraTarget();
	tempVec2 *= 5;
	tempVec2.y = 0;
	tempVec.y -= 2;
	glm::vec3 tempVec3 = tempVec + tempVec2;

	
	PlayerModel.set_ModelPosition(tempVec+tempVec2);
	
	PlayerModel.rotate_Model(glm::vec3(0.f, -TheCamera.get_CameraRotation().x, 0.f));
	set_GameObjectPosition(tempVec+tempVec2);
	
}

void Player::on_Collision(GameObject* otherGameObject)
{

}

void Player::jump()
{
	Jumping = true;
}
