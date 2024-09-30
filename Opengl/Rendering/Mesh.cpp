#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <OBJ_Loader/tiny_obj_loader.h>
#include <glad/glad.h>

#include <iostream>

#include "MeshData.h"
#include "../FlexLibrary/FlexMath/FlexMath.h"

void Mesh::load_MeshObj(const std::string& filePath)
{
    tinyobj::attrib_t attribute;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, error;

    if (!tinyobj::LoadObj(&attribute, &shapes, &materials, &warning, &error, filePath.c_str(), 0, true))
    {
        throw std::runtime_error(warning + error);
    }

	Vertices.reserve(attribute.vertices.size() / 3);

	/*for (size_t sIndex = 0; sIndex < shapes.size(); sIndex++)
	{
		size_t index_Offset = 0;
		for (size_t fIndex = 0; fIndex < shapes[sIndex].mesh.num_face_vertices.size(); fIndex++)
		{
			size_t faceVertices = size_t(shapes[sIndex].mesh.num_face_vertices[fIndex]);

			for (size_t vIndex = 0; vIndex < faceVertices; vIndex++)
			{
				Vertex tempVertex;

				tinyobj::index_t index = shapes[sIndex].mesh.indices[index_Offset + vIndex];

				tempVertex.Position = { attribute.vertices[(3 * index.vertex_index) + 0],
									attribute.vertices[(3 * index.vertex_index) + 1],
									attribute.vertices[(3 * index.vertex_index) + 2]
				};

				if (index.normal_index >= 0)
				{
					tempVertex.Normal = { attribute.normals[(3 * index.normal_index) + 0],
										attribute.normals[(3 * index.normal_index) + 1],
										attribute.normals[(3 * index.normal_index) + 2]
					};
				}

				if (index.texcoord_index >= 0)
				{
					tempVertex.Texture = { attribute.texcoords[(2 * index.texcoord_index) + 0],
										attribute.texcoords[(2 * index.texcoord_index) + 1],
					};
				}

				Vertices.emplace_back(tempVertex);

				index_Offset += faceVertices;

				shapes[sIndex].mesh.material_ids[fIndex];
			}
		}
	}*/

	int textureCordIndex = 0;
    for (size_t i = 0; i < attribute.vertices.size(); i+=3)
    {
		Vertex tempVertex;
		tempVertex.Position = {attribute.vertices[i], attribute.vertices[i+1] , attribute.vertices[i+2] };
		//tempVertex.Color = { attribute.colors[i], attribute.colors[i + 1] , attribute.colors[i + 2] };
		tempVertex.Color = glm::vec3(0.5f);
		tempVertex.Texture = { attribute.texcoords[textureCordIndex], attribute.texcoords[textureCordIndex + 1] };
		//tempVertex.Normal = { attribute.normals[i], attribute.normals[i + 1] , attribute.normals[i + 2] };
		textureCordIndex += 2;

		Vertices.emplace_back(tempVertex);
    }

	for (auto shape = shapes.begin(); shape < shapes.end(); ++shape)
	{
		std::vector<tinyobj::index_t>& indices = shape->mesh.indices;
		std::vector<int>& material_Ids = shape->mesh.material_ids;

		for (size_t index = 0; index < material_Ids.size(); index++)
		{
			Triangle tempTriangle(indices[3 * index].vertex_index, indices[3 * index + 1].vertex_index, indices[3 * index + 2].vertex_index);
			Triangles.emplace_back(tempTriangle);
		}
	}

    for (const Triangle& triangle : Triangles)
    {
		FLXMath::calculate_TriangleNormal(Vertices[triangle.FirstIndex], Vertices[triangle.SecondIndex], Vertices[triangle.ThirdIndex]);
    }

    bind_Buffer(GL_STATIC_DRAW);
}

void Mesh::load_MeshTxt(const std::string& filePath)
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
			Vertices.reserve(static_cast<unsigned int>(vectorSize));
			continue;
		}

		if (file.peek() == 'T')
		{
			std::getline(file, line);
			dataType = 'T';
			file >> vectorSize;
			Triangles.reserve(static_cast<unsigned int>(vectorSize));

			continue;
		}

		switch (dataType)
		{
		case 'V':
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 color;
			file >> position.x >> position.y >> position.z >> normal.x >> normal.y >> normal.z >> color.r >> color.g >> color.b;
			Vertices.emplace_back(position, normal, color, glm::vec2(0.0f));
			break;

		case 'T':
			int I_1, I_2, I_3;
			file >> I_1 >> I_2 >> I_3;
			Triangles.emplace_back(I_1, I_2, I_3);
			break;

		default:
			break;
		}
	}

	bind_Buffer(GL_STATIC_DRAW);
}

void Mesh::create_CubeMesh()
{
	Vertices.emplace_back(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(0.0f, 1.0f));
	Vertices.emplace_back(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(0.0f, 0.0f));
	Vertices.emplace_back(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(1.0f, 1.0f));
	Vertices.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(1.0f, 0.0f));

	Vertices.emplace_back(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(1.0f, 1.0f));
	Vertices.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(1.0f, 0.0f));
	Vertices.emplace_back(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(0.0f, 0.0f));
	Vertices.emplace_back(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.f), glm::vec3(0.5f), glm::vec2(0.0f, 1.0f));

	Triangles.emplace_back(0, 1, 2);

	Triangles.emplace_back(2, 3, 0);

	Triangles.emplace_back(0, 4, 5);

	Triangles.emplace_back(5, 1, 0);

	Triangles.emplace_back(3, 2, 6);

	Triangles.emplace_back(6, 7, 3);

	Triangles.emplace_back(1, 5, 6);

	Triangles.emplace_back(6, 2, 1);

	Triangles.emplace_back(0, 3, 7);

	Triangles.emplace_back(7, 4, 0);

	Triangles.emplace_back(4, 7, 6);

	Triangles.emplace_back(6, 5, 4);

	for (const Triangle& triangle : Triangles)
	{
		FLXMath::calculate_TriangleNormal(Vertices[triangle.FirstIndex], Vertices[triangle.SecondIndex],
			Vertices[triangle.ThirdIndex]);
	}

	bind_Buffer(GL_STATIC_DRAW);
}

void Mesh::bind_Buffer(int drawType)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(Vertices.size() * sizeof(Vertex)), Vertices.data(), drawType);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  static_cast<GLsizeiptr>(Triangles.size() * sizeof(Triangle)), Triangles.data(), drawType);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24),
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)36),

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::rebind_Buffer(int drawType)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), drawType);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Triangles.size() * sizeof(Triangle), Triangles.data(), drawType);
}

void Mesh::delete_Buffer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::bind_VAOBuffer()
{
	glBindVertexArray(VAO);
}
