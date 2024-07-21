#include "Light.h"

#include "../Engine/EngineManager.h"

void Light::init_Light()
{
	EngineManager::get()->get_ActiveScene()->add_LightToScene(this);
}

glm::vec3 Light::get_LightPosition() const
{
	return Position;
}

void Light::set_LightPosition(const glm::vec3& newPosition)
{
	Position = newPosition;
}

glm::vec3 Light::get_LightColor() const
{
	return color;
}

void Light::set_LightColor(const glm::vec3& newColor)
{
	color = newColor;
}
