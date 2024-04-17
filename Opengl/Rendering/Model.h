#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include "glad/glad.h"

class GameObject;
class Mesh;

struct Vertex
{
	//Vertex() = default;
	Vertex(const glm::vec3& position, const glm::vec3& color) :
		Position(position), Color(color){}
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& color) :
		Position(position), Normal(normal), Color(color){}

	glm::vec3 Position = glm::vec3(0.f);
	glm::vec3 Normal = glm::vec3(0.f);
	glm::vec3 Color = glm::vec3(0.f);
};

struct Triangle
{
	Triangle(unsigned int firstIndex, unsigned int secondIndex, unsigned int thirdIndex) :
		FirstIndex(firstIndex), SecondIndex(secondIndex), ThirdIndex(thirdIndex){}

	unsigned int FirstIndex;
	unsigned int SecondIndex;
	unsigned int ThirdIndex;
};

class Model
{
public:
	//std::vector<Vertex> Vertices;
	//std::vector<Triangle> Indices;
	Mesh* ModelMesh;

	void init_Model();
	//void load_Model(std::string& filePath);
	//void bind_Buffer();
	void set_ModelMesh(Mesh* modelMesh);
	void create_NewMesh();

	void bind_ToGameObject(GameObject* GO);
	void attach_ToPosition(glm::vec3* attachedPosition);
	void hide_Model(bool hidingModel);
	void set_ModelPosition(glm::vec3 newPosition);
	void scale_Model(glm::vec3 newScale);
	void rotate_Model(glm::vec3 newRotation);
	void draw_ModelAsLines(bool drawModelLines);
	glm::vec3 get_WorldPosition();

	void turn_OnLine();

	void draw_Model();
	glm::mat4 get_ModelMatrix() const;

private:
	//unsigned int VAO;
	//unsigned int VBO;
	//unsigned int EBO;
	bool HidingModel = false;
	bool DrawLines = false;
	bool IsLine = false;


	glm::vec3* AttachedModelPosition = nullptr;
	glm::vec3 ModelPosition = glm::vec3(0.f);
	glm::vec3 ModelScale = glm::vec3(1.f);
	glm::vec3 ModelRotation = glm::vec3(0.f);

	void cleanup_Model();
};

void load_Model(std::string& filePath, Mesh& mesh);
void create_Cube(Mesh& model, const glm::vec3& color);
void create_SphereLines(Mesh& lineModel, float radius, const glm::vec3& color);
void create_BoxLines(Mesh& lineModel, float height, float width, float depth, const glm::vec3& color);
float line_Function(float x);
void create_LinesOnTerrain(Mesh& lineModel, float xStart, float xEnd, float deltaX);

void calculate_VertexNormal(Vertex& vertexA, const Vertex& vertexB, const Vertex& vertexC, const Vertex& vertexD);
void calculate_TriangleNormal(Vertex& vertexA, Vertex& vertexB, Vertex& vertexC);
int find_Interval(float value);
void calculate_BSplineCurve();
