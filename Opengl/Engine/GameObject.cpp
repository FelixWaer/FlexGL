#include "GameObject.h"

#include "EngineManager.h"
#include "SceneManager.h"
#include "../FlexLibrary/FlexTimer/Flextimer.h"

void GameObject::init_GameObject()
{
	ParentScene = EngineManager::get()->get_ActiveScene();
	ObjectID = ParentScene->add_GameObjectToScene(this);
}

void GameObject::tick(float deltaTime)
{
}

void GameObject::game_Start()
{
}

uint32_t GameObject::get_GameObjectID()
{
	return ObjectID;
}

void GameObject::set_GameObjectPosition(glm::vec3 newPosition)
{
	ParentScene->get_ObjectHandler().set_ObjectPosition(ObjectID, newPosition);
}

glm::vec3& GameObject::get_GameObjectPosition()
{
	return ParentScene->get_ObjectHandler().get_ObjectPosition(ObjectID);
}

glm::vec3* GameObject::get_GameObjectPositionPtr()
{
	return &TempPosition;
}

void GameObject::set_GameObjectVelocity(const glm::vec3& newVelocity)
{
	ParentScene->get_ObjectHandler().set_ObjectVelocity(ObjectID, newVelocity);
}

glm::vec3& GameObject::get_GameObjectVelocity()
{
	return ParentScene->get_ObjectHandler().get_ObjectVelocity(ObjectID);
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
