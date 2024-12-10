#include "Model.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

#include "../Engine/EngineManager.h"
//#include "../Engine/GameObject.h"

#include "../FlexLibrary/FlexTimer/Flextimer.h"

void Model::init_Model()
{
	ParentScene = EngineManager::get()->get_ActiveScene();
	//ModelID = ParentScene->add_ModelToScene(this);
}

void Model::attach_ToGameObject(GameObject* GO)
{
	ParentObject = GO;
}


void Model::attach_ToPosition(glm::vec3* attachedPosition)
{
	AttachedPosition = attachedPosition;
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

glm::vec3& Model::get_ModelPosition()
{
	if (ParentObject == nullptr)
	{
		return ModelPosition;
	}
	//return ParentObject->get_GameObjectPosition();
}

void Model::set_ModelPosition(glm::vec3 newPosition)
{
	//ParentScene->get_ModelHandler().set_ModelPosition(ModelID, newPosition);
	ModelPosition = newPosition;
}

void Model::calculate_ModelMatrix()
{
	if (ParentObject == nullptr)
	{
		ModelMatrix = glm::translate(glm::mat4(1.f), ModelPosition);
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ModelRotation.x), glm::vec3(1.f, 0.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ModelRotation.z), glm::vec3(0.f, 0.f, 1.f));
		ModelMatrix = glm::scale(ModelMatrix, ModelScale);

		return;
	}

	//might be the faster method for calculating
	//ModelMatrix = glm::translate(glm::mat4(1.f), ParentObject->get_GameObjectPosition());
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ModelRotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(ModelRotation.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, ModelScale);
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
