#include "SphereCollision.h"

#include "../Engine/EngineManager.h"
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../Rendering/Renderer.h"

void SphereCollision::attach_ToGameObject(GameObject* GO)
{
	AttachedGameObject = GO;
	SpherePosition = GO->get_GameObjectPositionPtr();
	EngineManager::get_Engine()->add_ToSphereCollisionHandler(this);
}

void SphereCollision::enable_Collider(bool isColliding)
{
	
}

void SphereCollision::enable_SphereVisible(bool isVisible)
{
	if (isVisible == true && SphereModel == nullptr)
	{
		SphereModel = new Model;
		SphereModel->init_Model();
		SphereModel->attach_ToPosition(SpherePosition);
		SphereModel->turn_OnLine();
		SphereModel->set_ModelMesh(&Renderer::get()->DebugSphere);
		SphereModel->scale_Model(glm::vec3(SphereRadius, SphereRadius, SphereRadius));

		return;
	}
	if (isVisible == false && SphereModel != nullptr)
	{
		SphereModel->hide_Model(true);
	}
}

void SphereCollision::set_SphereRadius(float radius)
{
	SphereRadius = radius;
	if (SphereModel != nullptr)
	{
		SphereModel->scale_Model(glm::vec3(radius, radius, radius));
	}
}

float SphereCollision::get_SphereRadius() const
{
	return SphereRadius;
}

glm::vec3 SphereCollision::get_SpherePosition() const
{
	return *SpherePosition;
}

GameObject* SphereCollision::get_AttachedGameObject()
{
	return AttachedGameObject;
}

void SphereCollision::run_CollisionFunction(SphereCollision* otherSphereCollider)
{
	AttachedGameObject->on_Collision(otherSphereCollider->get_AttachedGameObject());
}
