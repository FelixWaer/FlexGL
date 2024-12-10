#pragma once
#include "Entity.h"

class Cube : public Entity
{
public:
	void tick(float deltaTime) override;

protected:
	void init_Entity() override;

private:
	Entity* testEntity = nullptr;
};

