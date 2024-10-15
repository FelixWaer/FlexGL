#pragma once
#include <queue>
#include <vector>
#include <glm/glm.hpp>

class Model;

class ModelHandler
{
public:
	uint32_t add_ModelToHandler(Model* model);
	void remove_ModelFromHandler(uint32_t modelID);

	glm::vec3& get_ModelPosition(uint32_t modelID);
	void set_ModelPosition(uint32_t modelID, const glm::vec3& newPosition);
	void set_ModelPosition(uint32_t modelID, glm::vec3&& newPosition);
	glm::vec3& get_ModelRotation(uint32_t modelID);
	void set_ModelRotation(uint32_t modelID, const glm::vec3& newRotation);
	void set_ModelRotation(uint32_t modelID, glm::vec3&& newRotation);
	glm::vec3& get_ModelScale(uint32_t modelID);
	void set_ModelScale(uint32_t modelID, const glm::vec3& newScale);
	void set_ModelScale(uint32_t modelID, glm::vec3&& newScale);
	glm::mat4& get_ModelMatrix(uint32_t modelID);
	void calculate_Matrices();
	void calculate2DMatrices();

private:
	std::vector<Model*> Models;
	std::vector<glm::vec3> Positions;
	std::vector<glm::vec3> Rotations;
	std::vector<glm::vec3> Scales;
	std::vector<glm::mat4> Matrices;
	std::queue<uint32_t> AvailableModelIDs;

	uint32_t NumberOfModels = 0;
};

