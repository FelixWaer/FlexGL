#include "Model.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

#include "../Engine/EngineManager.h"
#include "../Engine/GameObject.h"

void Model::init_Model()
{
	EngineManager::get()->get_ActiveScene()->add_ModelToScene(this);
}

void Model::attach_ToGameObject(GameObject* GO)
{
	AttachedModelPosition = GO->get_GameObjectPositionPtr();
	AttachedObjectID = GO->get_GameObjectID();
}

void Model::attach_ToPosition(glm::vec3* attachedPosition)
{
	AttachedModelPosition = attachedPosition;
}

bool Model::is_ModelHidden() const
{
	return HidingModel;
}

void Model::hide_Model(bool hidingModel)
{
	HidingModel = hidingModel;
}

glm::vec3& Model::get_ModelScale()
{
	return ModelScale;
}

void Model::scale_Model(glm::vec3 newScale)
{
	ModelScale = newScale;
}

glm::vec3& Model::get_ModelRotation()
{
	return ModelRotation;
}

void Model::rotate_Model(glm::vec3 newRotation)
{
	ModelRotation = newRotation;
}

glm::vec3 Model::get_ModelPosition() const
{
	if (AttachedModelPosition == nullptr)
	{
		return ModelPosition;
	}
	return *AttachedModelPosition;
}

void Model::set_ModelPosition(glm::vec3 newPosition)
{
	ModelPosition = newPosition;
}

glm::mat4 Model::get_ModelMatrix() const
{
	glm::mat4 test(1.f);
	test = glm::translate(glm::mat4(1.f), );
	test *= glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.x), glm::vec3(1.f, 0.f, 0.f));
	test *= glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f));
	test *= glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.z), glm::vec3(0.f, 0.f, 1.f));
	return glm::scale(test, ModelScale);
}

std::string& Model::get_ModelMeshName()
{
	return ModelMeshName;
}

void Model::set_ModelMesh(const std::string& newMeshName)
{
	ModelMeshName = newMeshName;
}

std::string& Model::get_ModelMaterialName()
{
	return ModelMaterial;
}

void Model::set_ModelMaterial(const std::string& newMaterialName)
{
	ModelMaterial = newMaterialName;
}
