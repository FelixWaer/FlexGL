#include "BoxCollision.h"

#include "../Engine/EngineManager.h"
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../Rendering/Renderer.h"

void BoxCollision::attach_ToGameObject(GameObject* GO)
{
	AttachedGameObject = GO;
	BoxPosition = GO->get_GameObjectPositionPtr();
	EngineManager::TheEngineManager->add_ToBoxCollisionHandler(this);
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
		BoxModel->draw_ModelAsLines(true);
		BoxModel->attach_ToPosition(BoxPosition);
		BoxModel->set_ModelMesh(&Renderer::get()->Cube);
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

void BoxCollision::run_CollisionFunction(BoxCollision* otherBoxCollider)
{
	AttachedGameObject->on_Collision(otherBoxCollider->get_AttachedGameObject());
}

