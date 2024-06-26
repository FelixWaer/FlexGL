#include "PickUpItem.h"

#include <iostream>

#include "../Engine/EngineManager.h"
#include "../Rendering/Renderer.h"

void PickUpItem::game_Start()
{
    ItemModel = new Model();
    ItemModel->init_Model();
    ItemModel->set_ModelMesh(&Renderer::get()->TestLoadMesh);
    ItemModel->bind_ToGameObject(this);
    ItemModel->scale_Model(glm::vec3(0.1f));
    Collider.attach_ToGameObject(this);
    Collider.set_SphereRadius(7.f);
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
