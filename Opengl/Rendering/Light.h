#pragma once
#include <glm/glm.hpp>

#include "Model.h"

class Light
{
public:
	void init_Light();

	glm::vec3 get_LightPosition() const;
	void set_LightPosition(const glm::vec3& newPosition);
	glm::vec3 get_LightColor() const;
	void set_LightColor(const glm::vec3& newColor);

private:
	glm::vec3 Position = glm::vec3(0.f);
	glm::vec3 color = glm::vec3(0.5f);
};

