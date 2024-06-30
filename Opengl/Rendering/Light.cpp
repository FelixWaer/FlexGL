#include "Light.h"

#include "Renderer.h"

void Light::init_Light()
{
	LightModel.init_Model();
	LightModel.set_ModelMesh(&Renderer::get()->LightCube);
	LightModel.set_ModelPosition(Position);
	LightModel.scale_Model(glm::vec3(10.f));
}

glm::vec3 Light::get_LightPosition() const
{
	return Position;
}

void Light::set_LightPosition(const glm::vec3& newPosition)
{
	Position = newPosition;
	LightModel.set_ModelPosition(Position);
}

glm::vec3 Light::get_LightColor() const
{
	return color;
}

void Light::set_LightColor(const glm::vec3& newColor)
{
	color = newColor;
}
