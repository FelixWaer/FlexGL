#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <unordered_map>

#include "OBJ_Loader/tiny_obj_loader.h"
#include "glad/glad.h"
#include "Model.h"

#include "Vertex.h"

void Mesh::load_Model(const char* filePath)
{
    tinyobj::attrib_t attribute;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, error;

    if (!tinyobj::LoadObj(&attribute, &shapes, &materials, &warning, &error, filePath, 0, true))
    {
        throw std::runtime_error(warning + error);
    }

	Vertices.reserve(attribute.vertices.size()/3);
	int textureCordIndex = 0;
    for (size_t i = 0; i < attribute.vertices.size(); i+=3)
    {
		Vertex tempVertex;
		tempVertex.Position = {attribute.vertices[i], attribute.vertices[i+1] , attribute.vertices[i+2] };
		tempVertex.Color = { attribute.colors[i], attribute.colors[i + 1] , attribute.colors[i + 2] };
	/*	tempVertex.Texture = { attribute.texcoords[textureCordIndex], attribute.texcoords[textureCordIndex + 1] };
		tempVertex.Normal = { attribute.normals[i], attribute.normals[i + 1] , attribute.normals[i + 2] };*/
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
		calculate_TriangleNormal(Vertices[triangle.FirstIndex], Vertices[triangle.SecondIndex], Vertices[triangle.ThirdIndex]);
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
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), drawType);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Triangles.size() * sizeof(Triangle), Triangles.data(), drawType);

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
	
}
