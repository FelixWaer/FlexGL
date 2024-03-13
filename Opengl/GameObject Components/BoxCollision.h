#pragma once

#include "glm/glm.hpp"

class GameObject;
class Model;

class BoxCollision
{
public:
	void attach_ToGameObject(GameObject* GO);
	void enable_Collider(bool isColliding);
	void enable_BoxVisible(bool isVisible);
	glm::vec3 get_BoxPosition() const;
	GameObject* get_AttachedGameObject();
	void set_BoxHeight(float height);
	void set_BoxWidth(float width);
	void set_BoxDepth(float depth);

	float BoxWidth = 0.f;
	float BoxHeight = 0.f;
	float BoxDepth = 0.f;

	void run_CollisionFunction(BoxCollision* otherBoxCollider);
private:
	glm::vec3* BoxPosition = nullptr;
	GameObject* AttachedGameObject = nullptr;
	bool Visible = false;
	bool Collision = true;

	Model* BoxModel;
};

