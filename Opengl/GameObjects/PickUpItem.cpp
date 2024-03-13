#include "PickUpItem.h"

#include <iostream>

#include "../EngineManager.h"

void PickUpItem::game_Start()
{
    Model.init_Model();
    create_Cube(Model, glm::vec3(1.f, 0.f, 0.f));
	Model.bind_ToGameObject(this);
    Collider.attach_ToGameObject(this);
    Collider.set_SphereRadius(5.f);
    Collider.enable_SphereVisible(true);
    BoxCollider.attach_ToGameObject(this);
    BoxCollider.set_BoxHeight(10.f);
    BoxCollider.set_BoxWidth(10.f);
    BoxCollider.set_BoxDepth(10.f);
    BoxCollider.enable_BoxVisible(true);
}

void PickUpItem::tick(float deltaTime)
{
    GameObject::tick(deltaTime);
}

void PickUpItem::on_Collision(GameObject* otherGameObject)
{
	if (otherGameObject->has_Tag("Player"))
	{
        Model.hide_Model(true);
        Collider.enable_SphereVisible(false);
	}
}

void PickUpItem::update_Position(glm::vec3 newPosition)
{
    set_GameObjectPosition(newPosition);
}
