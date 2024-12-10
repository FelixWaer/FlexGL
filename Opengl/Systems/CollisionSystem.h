#pragma once
#include "System.h"

class CollisionSystem : public System
{
public:
	void update(float deltaTime) override;

private:
	bool calculate_SphereCollision(glm::vec3& sphereA, float radiusA, glm::vec3& sphereB, float radiusB);
	bool calculate_BoxCollsion();
};

