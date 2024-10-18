#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

struct TransformComponent
{
	glm::vec3 Rotation = glm::vec3(0.f);
	glm::vec3 Scale = glm::vec3(1.f);
	glm::mat4 Matrix = glm::mat4(1.f);
};
