#include "NPC.h"

#include "../Engine/EngineManager.h"

void NPC::game_Start()
{
	NPCModel.init_Model();
	create_Cube(NPCModel, glm::vec3(0.8f, 0.5f, 0.5f));
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

