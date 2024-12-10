#pragma once
#include "System.h"

class MovementSystem : public System
{
public:
	void update(float deltaTime) override;

private:
	float Timer = 0.f;
};

