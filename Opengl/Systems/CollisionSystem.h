#pragma once
#include "System.h"

class CollisionSystem : public System
{
public:
	void update(float deltaTime) override;

private:
	//bool calculate_Collision();
};

