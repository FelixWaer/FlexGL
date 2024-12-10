#pragma once
#include "System.h"

class ParticleSystem : public System
{
public:
	void init() override;
	void update(float deltaTime) override;

private:
	float Timer = 0.f;
};

