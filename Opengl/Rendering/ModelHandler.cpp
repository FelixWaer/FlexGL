#include "ModelHandler.h"

#include <glm/ext/matrix_transform.hpp>

#include "Model.h"
#include "../Engine/GameObject.h"
#include "../FlexLibrary/FlexTimer/Flextimer.h"

uint32_t ModelHandler::add_ModelToHandler(Model* model)
{
	if (AvailableModelIDs.empty() == true)
	{
		Models.emplace_back(model);
		Positions.emplace_back(0.f);
		Rotations.emplace_back(0.f);
		Scales.emplace_back(1.f);
		Matrices.emplace_back(glm::mat4(1.f));
		NumberOfModels++;
		return NumberOfModels - 1;
	}

	const uint32_t availableID = AvailableModelIDs.front();
	AvailableModelIDs.pop();
	Models[availableID] = model;
	return availableID;
}

void ModelHandler::remove_ModelFromHandler(uint32_t modelID)
{
	delete Models[modelID];
	Models[modelID] = nullptr;
	AvailableModelIDs.emplace(modelID);
}

glm::vec3& ModelHandler::get_ModelPosition(uint32_t modelID)
{
	return Positions[modelID];
}

void ModelHandler::set_ModelPosition(uint32_t modelID, const glm::vec3& newPosition)
{
	Positions[modelID] = newPosition;
}

void ModelHandler::set_ModelPosition(uint32_t modelID, glm::vec3&& newPosition)
{
	Positions[modelID] = newPosition;
}

glm::vec3& ModelHandler::get_ModelRotation(uint32_t modelID)
{
	return Rotations[modelID];
}

void ModelHandler::set_ModelRotation(uint32_t modelID, const glm::vec3& newRotation)
{
	Rotations[modelID] = newRotation;
}

void ModelHandler::set_ModelRotation(uint32_t modelID, glm::vec3&& newRotation)
{
	Rotations[modelID] = newRotation;
}

glm::vec3& ModelHandler::get_ModelScale(uint32_t modelID)
{
	return Scales[modelID];
}

void ModelHandler::set_ModelScale(uint32_t modelID, const glm::vec3& newScale)
{
	Scales[modelID] = newScale;
}

void ModelHandler::set_ModelScale(uint32_t modelID, glm::vec3&& newScale)
{
	Scales[modelID] = newScale;
}

glm::mat4& ModelHandler::get_ModelMatrix(uint32_t modelID)
{
	return Matrices[modelID];
}

void ModelHandler::calculate_Matrices()
{
	FlexTimer timer("Data Driven Matrix calculation");

	for (size_t id = 0; id < Matrices.size(); id++)
	{
		if (Models[id] == nullptr)
		{
			Matrices[id] = glm::translate(glm::mat4(1.f), Positions[id]);
			Matrices[id] *= glm::rotate(glm::mat4(1.f), glm::radians(Rotations[id].x), glm::vec3(1.f, 0.f, 0.f));
			Matrices[id] *= glm::rotate(glm::mat4(1.f), glm::radians(Rotations[id].y), glm::vec3(0.f, 1.f, 0.f));
			Matrices[id] *= glm::rotate(glm::mat4(1.f), glm::radians(Rotations[id].z), glm::vec3(0.f, 0.f, 1.f));
			Matrices[id] = glm::scale(Matrices[id], Scales[id]);

			return;
		}

		//might be the faster method for calculating
		Matrices[id] = glm::translate(glm::mat4(1.f), Models[id]->ParentObject->get_GameObjectPosition());
		Matrices[id] = glm::rotate(Matrices[id], glm::radians(Rotations[id].x), glm::vec3(1.f, 0.f, 0.f));
		Matrices[id] = glm::rotate(Matrices[id], glm::radians(Rotations[id].y), glm::vec3(0.f, 1.f, 0.f));
		Matrices[id] = glm::rotate(Matrices[id], glm::radians(Rotations[id].z), glm::vec3(0.f, 0.f, 1.f));
		Matrices[id] = glm::scale(Matrices[id], Scales[id]);
	}
}

void ModelHandler::calculate2DMatrices()
{
	FlexTimer timer("Data Driven 2D Matrix calculation");

	for (size_t id = 0; id < Matrices.size(); id++)
	{
		if (Models[id] == nullptr)
		{
			Matrices[id] = glm::mat4(1.f);
			return;
		}

		Matrices[id] = glm::translate(glm::mat4(1.f), Positions[id]);
		Matrices[id] = glm::scale(Matrices[id], glm::vec3(Models[id]->get_ModelScale().x, Models[id]->get_ModelScale().y, 1.0f));
	}
}
