#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>

class GameObject;

class Model
{
public:
	void init_Model();

	void attach_ToGameObject(GameObject* GO);
	void attach_ToPosition(glm::vec3* attachedPosition);

	//Model Hidden
	bool is_ModelHidden() const;
	void hide_Model(bool hidingModel);

	//Model Scale
	glm::vec3& get_ModelScale();
	void scale_Model(glm::vec3 newScale);

	//Model Rotation
	glm::vec3& get_ModelRotation();
	void rotate_Model(glm::vec3 newRotation);

	//Model Position
	glm::vec3 get_ModelPosition() const;
	void set_ModelPosition(glm::vec3 newPosition);

	//Model Matrix
	glm::mat4 get_ModelMatrix() const;

	//Model Mesh
	std::string& get_ModelMeshName();
	void set_ModelMesh(const std::string& newMeshName);

	//Model Material
	std::string& get_ModelMaterialName();
	void set_ModelMaterial(const std::string& newMaterialName);

private:
	std::string ModelMeshName = "Cube";
	std::string ModelMaterial = "BasicMaterial";
	uint32_t AttachedObjectID = 0;

	bool HidingModel = false;

	glm::vec3* AttachedModelPosition = nullptr;
	glm::vec3 ModelPosition = glm::vec3(0.f);
	glm::vec3 ModelScale = glm::vec3(1.f);
	glm::vec3 ModelRotation = glm::vec3(0.f);
};
