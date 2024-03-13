#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include "glad/glad.h"

class GameObject;

struct Vertex
{
public:
	Vertex() = default;
	Vertex(float x, float y, float z, const glm::vec3& color);

	float x, y, z;
	glm::vec3 RGB;
};

class Model
{
public:
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	void init_Model();
	void load_Model(std::string& filePath);
	void bind_Buffer();
	void bind_ToGameObject(GameObject* GO);
	void attach_ToPosition(glm::vec3* attachedPosition);
	void hide_Model(bool hidingModel);
	void set_ModelPosition(glm::vec3 newPosition);
	void scale_Model(glm::vec3 newScale);
	void rotate_Model(glm::vec3 newRotation);
	void draw_ModelAsLines(bool drawModelLines);

	void draw_Model();
	glm::mat4 get_ModelMatrix() const;

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	bool HidingModel = false;
	bool DrawLines = false;

	glm::vec3* AttachedModelPosition = nullptr;
	glm::vec3 ModelPosition;
	glm::vec3 ModelScale;
	glm::vec3 ModelRotation;

	void cleanup_Model();
};

class Line
{
public:
	Line(bool isLine);

	std::vector<Vertex> Vertices;

	void init_LineModel();
	void load_LineModel(std::string& filePath);
	void bind_Buffer();
	void draw_Line();
	glm::mat4 get_LineMatrix() const;
	void set_Location(glm::vec3 posVector);
	void bind_ToGameObject(GameObject* GO);
	void attach_ToPosition(glm::vec3* attachedPosition);
	void hide_LineModel(bool hidingModel);

private:
	glm::vec3* AttachedLineModelPosition = nullptr;
	glm::vec3 LineModelPosition;
	unsigned int VAO;
	unsigned int VBO;
	bool IsLine;
	bool HidingModel = false;

	void cleanup_LineModel();
};

void create_Cube(Model& model, const glm::vec3& color);
void create_SphereLines(Line& lineModel, float radius, const glm::vec3& color);
void create_BoxLines(Line& lineModel, float height, float width, float depth, const glm::vec3& color);
