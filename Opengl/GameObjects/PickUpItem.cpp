#include "PickUpItem.h"

#include <iostream>

#include "../Engine/EngineManager.h"

void PickUpItem::game_Start()
{
    ItemModel = new Model();
    ItemModel->init_Model();
    create_Cube(*ItemModel, Color);
    ItemModel->bind_ToGameObject(this);
    Collider.attach_ToGameObject(this);
    Collider.set_SphereRadius(3.f);
    Collider.enable_SphereVisible(true);
}

void PickUpItem::tick(float deltaTime)
{
    GameObject::tick(deltaTime);
}

void PickUpItem::on_Collision(GameObject* otherGameObject)
{
	if (otherGameObject->has_Tag("Player"))
	{
        ItemModel->hide_Model(true);
        Collider.enable_SphereVisible(false);
	}
}

void PickUpItem::update_Position(glm::vec3 newPosition)
{
    set_GameObjectPosition(newPosition);
}

void PickUpItem::set_Color(const glm::vec3& color)
{
    Color = color;
}
