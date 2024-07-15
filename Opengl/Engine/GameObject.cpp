#include "GameObject.h"

#include "EngineManager.h"

void GameObject::init_GameObject()
{
	EngineManager::get()->get_ActiveScene()->add_GameObjectToScene(this);
}

void GameObject::tick(float deltaTime)
{
	GameObjectPosition += GameObjectVelocity * deltaTime;
	GameObjectVelocity = glm::vec3(0.f);
}

void GameObject::game_Start()
{
}

void GameObject::on_Collision(GameObject* otherGameObject)
{
}

void GameObject::set_GameObjectPosition(glm::vec3 newPosition)
{
	GameObjectPosition = newPosition;
}

glm::vec3& GameObject::get_GameObjectPosition()
{
	return GameObjectPosition;
}

glm::vec3* GameObject::get_GameObjectPositionPtr()
{
	return &GameObjectPosition;
}

void GameObject::set_GameObjectVelocity(const glm::vec3& newVelocity)
{
	GameObjectVelocity += newVelocity;
}

glm::vec3& GameObject::get_GameObjectVelocity()
{
	return GameObjectVelocity;
}

void GameObject::set_GameObjectFront(const glm::vec3& newFront)
{
	GameObjectFront = newFront;
}

glm::vec3& GameObject::get_GameObjectFront()
{
	return GameObjectFront;
}

void GameObject::add_Tag(const std::string& tag)
{
	tags.emplace_back(tag);
}

bool GameObject::has_Tag(const std::string& tag)
{
	for (std::string& string : tags)
	{
		if (tag == string)
		{
			return true;
		}
	}
	return false;
}
