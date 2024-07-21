#include "BoxCollision.h"

#include "../Engine/EngineManager.h"
#include "../Engine/EventCallback.h"
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"

void BoxCollision::attach_ToGameObject(GameObject* GO)
{
	AttachedGameObject = GO;
	BoxPosition = GO->get_GameObjectPositionPtr();
	EngineManager::get()->get_ActiveScene()->add_BoxColliderToScene(this);
}

void BoxCollision::attach_Event(Event* eventPtr)
{
	CollisionEvent = eventPtr;
}

void BoxCollision::enable_Collider(bool isColliding)
{

}

void BoxCollision::enable_BoxVisible(bool isVisible)
{
	if (isVisible == true && BoxModel == nullptr)
	{
		BoxModel = new Model;
		BoxModel->init_Model();
		//BoxModel->draw_ModelAsLines(true);
		BoxModel->attach_ToPosition(BoxPosition);
		BoxModel->scale_Model(glm::vec3(BoxWidth, BoxHeight, BoxDepth));

		return;
	}
	if (isVisible == false && BoxModel != nullptr)
	{
		BoxModel->hide_Model(true);
	}
}

glm::vec3 BoxCollision::get_BoxPosition() const
{
	return *BoxPosition;
}

GameObject* BoxCollision::get_AttachedGameObject()
{
	return AttachedGameObject;
}

void BoxCollision::set_BoxHeight(float height)
{
	BoxHeight = height;
}

void BoxCollision::set_BoxWidth(float width)
{
	BoxWidth = width;
}

void BoxCollision::set_BoxDepth(float depth)
{
	BoxDepth = depth;
}

void BoxCollision::call_CollisionEvent(BoxCollision* otherBoxCollider) const
{
	if (CollisionEvent != nullptr)
	{
		CollisionEvent->Collision_Event(otherBoxCollider->get_AttachedGameObject());
	}
}

