#pragma once

#include "glm/glm.hpp"

class GameObject;
class Model;
class Event;

class BoxCollision
{
public:
	void attach_ToGameObject(GameObject* GO);
	void attach_Event(Event* eventPtr);
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

	void call_CollisionEvent(BoxCollision* otherBoxCollider) const;
private:
	glm::vec3* BoxPosition = nullptr;
	GameObject* AttachedGameObject = nullptr;
	bool Visible = false;
	bool Collision = true;

	Event* CollisionEvent = nullptr;
	Model* BoxModel;
};

