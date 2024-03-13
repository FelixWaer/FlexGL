#pragma once

#include "glm/glm.hpp"

class GameObject;
class Line;

class SphereCollision
{
public:
	void attach_ToGameObject(GameObject* GO);
	void enable_Collider(bool isColliding);
	void enable_SphereVisible(bool isVisible);
	void set_SphereRadius(float radius);
	float get_SphereRadius() const;
	glm::vec3 get_SpherePosition() const;
	GameObject* get_AttachedGameObject();

	void run_CollisionFunction(SphereCollision* otherSphereCollider);

private:
	glm::vec3* SpherePosition = nullptr;
	GameObject* AttachedGameObject = nullptr;
	float SphereRadius = 0.f;
	bool Visible = false;
	bool Collision = true;

	Line* SphereModel;
};

