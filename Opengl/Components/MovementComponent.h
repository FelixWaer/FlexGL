#pragma once
#include "glm/vec3.hpp"

struct MovementComponent
{
	glm::vec3 Velocity = glm::vec3(0.f);
	glm::vec3 Acceleration = glm::vec3(0.f);
	float Speed = 0.f;
};