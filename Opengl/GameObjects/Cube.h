#pragma once
#include "Entity.h"

class Cube : public Entity
{
public:

protected:
	void init_Entity() override;

private:
	Entity* testEntity = nullptr;
};

