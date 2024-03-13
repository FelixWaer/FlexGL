#include "Door.h"

#include "../EngineManager.h"

void Door::game_Start()
{
	DoorModel.init_Model();
	create_Cube(DoorModel, glm::vec3(0.5f, 0.8f, 0.5f));
	DoorModel.bind_ToGameObject(this);

	set_GameObjectPosition(glm::vec3(0.f, -17.f, 10.f));
	DoorModel.scale_Model(glm::vec3(2.f, 6.f, 1.f));

	SphereCollider.attach_ToGameObject(this);
	SphereCollider.set_SphereRadius(3.f);
	SphereCollider.enable_SphereVisible(true);
}

void Door::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
	if (OpenDoor == true)
	{
		move_Door(deltaTime);
	}
}

void Door::on_Collision(GameObject* otherGameObject)
{
	if (otherGameObject->has_Tag("Player"))
	{
		OpenDoor = true;
	}
}

void Door::move_Door(float deltaTime)
{
	if ( get_GameObjectPosition().z < 11.f)
	{
		Velocity.z = 1.f;
	}
	else if (get_GameObjectPosition().x > -2.f)
	{
		Velocity.x = -1.f;
	}

	if(get_GameObjectPosition().z >= 11.f)
	{
		Velocity.z = 0.f;
	}
	if(get_GameObjectPosition().x <= -2.f)
	{
		Velocity.x = 1.f;
	}
	set_GameObjectVelocity(Velocity);
}
