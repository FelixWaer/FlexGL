#include "Model.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

#include "../Engine/EngineManager.h"
#include "../Engine/GameObject.h"
#include "Mesh.h"

void Model::init_Model()
{
	EngineManager::TheEngineManager->add_ToModelHandler(this);
}

//void Model::load_Model(std::string& filePath)
//{
//	std::ifstream file;
//	file.open(filePath);
//
//	if (file.is_open() == false)
//	{
//		std::cout << "could not open model file!" << std::endl;
//		return;
//	}
//
//	char dataType = 'O';
//	float vectorSize = 0;
//	std::string line;
//
//	while (file.eof() == false)
//	{
//		file >> std::ws;
//		if (file.peek() == EOF)
//		{
//			break;
//		}
//		if (file.peek() == 'V')
//		{
//			std::getline(file, line);
//			dataType = 'V';
//			file >> vectorSize;
//			Vertices.reserve(static_cast<unsigned int>(vectorSize));
//			continue;
//		}
//
//		if (file.peek() == 'T')
//		{
//			std::getline(file, line);
//			dataType = 'T';
//			file >> vectorSize;
//			Indices.reserve(static_cast<unsigned int>(vectorSize));
//
//			continue;
//		}
//
//		switch (dataType)
//		{
//		case 'V':
//			glm::vec3 position;
//			glm::vec3 normal;
//			glm::vec3 color;
//			file >> position.x >> position.y >> position.z >> normal.x >> normal.y >> normal.z >> color.r >> color.g >> color.b;
//			Vertices.emplace_back(position, normal, color);
//			break;
//
//		case 'T':
//			int I_1, I_2, I_3;
//			file >> I_1 >> I_2 >> I_3;
//			Indices.emplace_back(I_1, I_2, I_3);
//			break;
//
//		case 'O':
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	bind_Buffer();
//}

//void Model::bind_Buffer()
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(Triangle), Indices.data(), GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24),
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	glBindVertexArray(0);
//}

void Model::set_ModelMesh(Mesh* modelMesh)
{
	ModelMesh = modelMesh;
}

void Model::create_NewMesh()
{
	ModelMesh = new Mesh;
}

void Model::bind_ToGameObject(GameObject* GO)
{
	AttachedModelPosition = GO->get_GameObjectPositionPtr();
}

void Model::attach_ToPosition(glm::vec3* attachedPosition)
{
	AttachedModelPosition = attachedPosition;
}

void Model::hide_Model(bool hidingModel)
{
	HidingModel = hidingModel;
}

void Model::set_ModelPosition(glm::vec3 newPosition)
{
	ModelPosition = newPosition;
}

void Model::scale_Model(glm::vec3 newScale)
{
	ModelScale = newScale;
}

void Model::rotate_Model(glm::vec3 newRotation)
{
	ModelRotation = newRotation;
}

void Model::draw_ModelAsLines(bool drawModelLines)
{
	DrawLines = drawModelLines;
}

glm::vec3 Model::get_WorldPosition()
{
	if (AttachedModelPosition == nullptr)
	{
		return ModelPosition;
	}
	return *AttachedModelPosition;
}

void Model::turn_OnLine()
{
	IsLine = true;
}

void Model::draw_Model()
{
	if (HidingModel == true)
	{
		return;
	}
	glBindVertexArray(ModelMesh->VAO);
	if (IsLine == true)
	{
		glDrawArrays(GL_LINE_STRIP, 0, ModelMesh->Vertices.size());
		glBindVertexArray(0);
		return;
	}

	if (DrawLines == true)
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_LINES, ModelMesh->Triangles.size()*3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		return;
	}
	glDrawElements(GL_TRIANGLES, ModelMesh->Triangles.size()*3, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

glm::mat4 Model::get_ModelMatrix() const
{
	glm::scale(glm::translate(glm::mat4(1.f), ModelPosition), ModelScale);
	if (AttachedModelPosition == nullptr)
	{
		return glm::scale(glm::translate(glm::mat4(1.f), ModelPosition) * glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f)), ModelScale);
	}

	return glm::scale(glm::translate(glm::mat4(1.f), *AttachedModelPosition) * glm::rotate(glm::mat4(1.f), glm::radians(ModelRotation.y), glm::vec3(0.f, 1.f, 0.f)), ModelScale);
}

//void Model::cleanup_Model()
//{
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//}

void load_Model(std::string& filePath, Mesh& mesh)
{
	std::ifstream file;
	file.open(filePath);

	if (file.is_open() == false)
	{
		std::cout << "could not open model file!" << std::endl;
		return;
	}

	char dataType = 'O';
	float vectorSize = 0;
	std::string line;

	while (file.eof() == false)
	{
		file >> std::ws;
		if (file.peek() == EOF)
		{
			break;
		}
		if (file.peek() == 'V')
		{
			std::getline(file, line);
			dataType = 'V';
			file >> vectorSize;
			mesh.Vertices.reserve(static_cast<unsigned int>(vectorSize));
			continue;
		}

		if (file.peek() == 'T')
		{
			std::getline(file, line);
			dataType = 'T';
			file >> vectorSize;
			mesh.Triangles.reserve(static_cast<unsigned int>(vectorSize));

			continue;
		}

		switch (dataType)
		{
		case 'V':
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 color;
			file >> position.x >> position.y >> position.z >> normal.x >> normal.y >> normal.z >> color.r >> color.g >> color.b;
			mesh.Vertices.emplace_back(position, normal, color);
			break;

		case 'T':
			int I_1, I_2, I_3;
			file >> I_1 >> I_2 >> I_3;
			mesh.Triangles.emplace_back(I_1, I_2, I_3);
			break;

		case 'O':
			break;

		default:
			break;
		}
	}

	mesh.bind_Buffer();
}

void create_Cube(Mesh& mesh, const glm::vec3& color)
{
	mesh.Vertices.emplace_back(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.f), color);
	mesh.Vertices.emplace_back(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f), color);
	mesh.Vertices.emplace_back(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f), color);
	mesh.Vertices.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f), color);

	mesh.Vertices.emplace_back(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.f), color);
	mesh.Vertices.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f), color);
	mesh.Vertices.emplace_back(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f), color);
	mesh.Vertices.emplace_back(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.f), color);

	mesh.Triangles.emplace_back(0, 1, 2);

	mesh.Triangles.emplace_back(2, 3, 0);

	mesh.Triangles.emplace_back(0, 4, 5);

	mesh.Triangles.emplace_back(5, 1, 0);

	mesh.Triangles.emplace_back(3, 2, 6);

	mesh.Triangles.emplace_back(6 ,7 ,3);

	mesh.Triangles.emplace_back(1, 5, 6);

	mesh.Triangles.emplace_back(6, 2, 1);

	mesh.Triangles.emplace_back(0, 3, 7);

	mesh.Triangles.emplace_back(7, 4, 0);

	mesh.Triangles.emplace_back(4, 7, 6);

	mesh.Triangles.emplace_back(6, 5, 4);

	for (const Triangle& triangle : mesh.Triangles)
	{
		calculate_TriangleNormal(mesh.Vertices[triangle.FirstIndex], 
			mesh.Vertices[triangle.SecondIndex], mesh.Vertices[triangle.ThirdIndex]);
	}

	mesh.bind_Buffer();
}

void create_SphereLines(Mesh& lineModel, float radius, const glm::vec3& color)
{
	float degrees =22.5f;
	glm::vec3 position;
	for (int i = 0; i < 18; i++)
	{
		position = glm::vec3(radius * sin(glm::radians(degrees * i)), radius * cos(glm::radians(degrees * i)), 0.f);
		lineModel.Vertices.emplace_back(position, glm::vec3(1.f), color);
	}
	for (int i = 0; i < 21; i++)
	{
		position = glm::vec3(0.f, radius * cos(glm::radians(degrees * i)), radius * sin(glm::radians(degrees * i)));
		lineModel.Vertices.emplace_back(position, glm::vec3(1.f), color);
	}
	for (int i = 0; i < 18; i++)
	{
		position = glm::vec3(radius * sin(glm::radians(degrees * i)), 0.f, radius * cos(glm::radians(degrees * i)));
		lineModel.Vertices.emplace_back(position, glm::vec3(1.f), color);
	}

	lineModel.bind_Buffer();
}

void create_BoxLines(Mesh& lineModel, float height, float width, float depth, const glm::vec3& color)
{
	lineModel.Vertices.emplace_back(glm::vec3(width / 2, height / 2, depth / 2), glm::vec3(1.f), color);
	lineModel.Vertices.emplace_back(glm::vec3(-width / 2, height / 2, depth / 2), glm::vec3(1.f), color);

	lineModel.Vertices.emplace_back(glm::vec3(width / 2, -height / 2, depth / 2), glm::vec3(1.f), color);
	lineModel.Vertices.emplace_back(glm::vec3(-width / 2, -height / 2, depth / 2), glm::vec3(1.f), color);

	lineModel.Vertices.emplace_back(glm::vec3(width / 2, height / 2, -depth / 2), glm::vec3(1.f), color);
	lineModel.Vertices.emplace_back(glm::vec3(-width / 2, height / 2, -depth / 2), glm::vec3(1.f), color);

	lineModel.Vertices.emplace_back(glm::vec3(width / 2, -height / 2, -depth / 2), glm::vec3(1.f), color);
	lineModel.Vertices.emplace_back(glm::vec3(-width / 2, -height / 2, -depth / 2), glm::vec3(1.f), color);

	lineModel.bind_Buffer();
}

float line_Function(float x)
{
	return x*x-x;
}

void create_LinesOnTerrain(Mesh& lineModel, float xStart, float xEnd, float deltaX)
{
	for (float x = xStart; x <= xEnd; x += deltaX)
	{
		glm::vec3 vertexPos(x, 0.f, line_Function(x));
		glm::ivec2 lineChunkPosition;
		lineChunkPosition.x = static_cast<int32_t>(floor(x / 30));
		lineChunkPosition.y = static_cast<int32_t>(floor(line_Function(x) / 30));

		for (Chunk& chunk : Terrain::get_Terrain()->Chunks)
		{
			if (lineChunkPosition == chunk.ChunkPosition)
			{
				for (const Triangle& triangle : chunk.ChunkModel->ModelMesh->Triangles)
				{
					if (EngineManager::calculate_PointOnTriangle(vertexPos, chunk.ChunkModel->ModelMesh->Vertices[triangle.FirstIndex].Position,
						chunk.ChunkModel->ModelMesh->Vertices[triangle.SecondIndex].Position, 
						chunk.ChunkModel->ModelMesh->Vertices[triangle.ThirdIndex].Position, chunk.ChunkModel->get_WorldPosition()))
					{
						vertexPos.y += 0.1f;
						lineModel.Vertices.emplace_back(vertexPos, glm::vec3(0.f), glm::vec3(1.f, 0.f, 0.f));
						break;
					}
				}
				break;
			}
		}
	}
	lineModel.bind_Buffer();
}

void calculate_TriangleNormal(Vertex& vertexA, Vertex& vertexB, Vertex& vertexC)
{
	glm::vec3 normal = glm::cross(vertexB.Position - vertexA.Position, vertexC.Position - vertexA.Position);

	vertexA.Normal += glm::normalize(normal);
	vertexB.Normal += glm::normalize(normal);
	vertexC.Normal += glm::normalize(normal);
}
