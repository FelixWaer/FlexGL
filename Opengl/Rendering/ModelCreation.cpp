#include "ModelCreation.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "MeshData.h"
#include "Mesh.h"
#include "../FlexLibrary/FlexMath/FlexMath.h"

namespace FLXModel
{
	void create_Cube(Mesh& mesh, const glm::vec3& color, bool reverseNormals)
	{
		mesh.Vertices.emplace_back(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.f), color, glm::vec2(0.0f, 1.0f));
		mesh.Vertices.emplace_back(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.f), color, glm::vec2(0.0f, 0.0f));
		mesh.Vertices.emplace_back(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.f), color, glm::vec2(1.0f, 1.0f));
		mesh.Vertices.emplace_back(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.f), color, glm::vec2(1.0f, 0.0f));

		mesh.Vertices.emplace_back(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.f), color, glm::vec2(1.0f, 1.0f));
		mesh.Vertices.emplace_back(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.f), color, glm::vec2(1.0f, 0.0f));
		mesh.Vertices.emplace_back(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.f), color, glm::vec2(0.0f, 0.0f));
		mesh.Vertices.emplace_back(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.f), color, glm::vec2(0.0f, 1.0f));

		mesh.Triangles.emplace_back(0, 1, 2);

		mesh.Triangles.emplace_back(2, 3, 0);

		mesh.Triangles.emplace_back(0, 4, 5);

		mesh.Triangles.emplace_back(5, 1, 0);

		mesh.Triangles.emplace_back(3, 2, 6);

		mesh.Triangles.emplace_back(6, 7, 3);

		mesh.Triangles.emplace_back(1, 5, 6);

		mesh.Triangles.emplace_back(6, 2, 1);

		mesh.Triangles.emplace_back(0, 3, 7);

		mesh.Triangles.emplace_back(7, 4, 0);

		mesh.Triangles.emplace_back(4, 7, 6);

		mesh.Triangles.emplace_back(6, 5, 4);

		for (const Triangle& triangle : mesh.Triangles)
		{
			if (reverseNormals == true)
			{
				FLXMath::calculate_TriangleNormal(mesh.Vertices[triangle.FirstIndex],
					mesh.Vertices[triangle.ThirdIndex], mesh.Vertices[triangle.SecondIndex]);
			}
			else
			{
				FLXMath::calculate_TriangleNormal(mesh.Vertices[triangle.FirstIndex],
					mesh.Vertices[triangle.SecondIndex], mesh.Vertices[triangle.ThirdIndex]);
			}
		}

		mesh.bind_Buffer(GL_STATIC_DRAW);
	}

	void create_SphereLines(Mesh& lineModel, float radius, const glm::vec3& color)
	{
		float degrees = 22.5f;
		glm::vec3 position;
		for (int i = 0; i < 18; i++)
		{
			position = glm::vec3(radius * sin(glm::radians(degrees * i)), radius * cos(glm::radians(degrees * i)), 0.f);
			lineModel.Vertices.emplace_back(position, glm::vec3(1.f), color, glm::vec2(0.0f));
		}
		for (int i = 0; i < 21; i++)
		{
			position = glm::vec3(0.f, radius * cos(glm::radians(degrees * i)), radius * sin(glm::radians(degrees * i)));
			lineModel.Vertices.emplace_back(position, glm::vec3(1.f), color, glm::vec2(0.0f));
		}
		for (int i = 0; i < 18; i++)
		{
			position = glm::vec3(radius * sin(glm::radians(degrees * i)), 0.f, radius * cos(glm::radians(degrees * i)));
			lineModel.Vertices.emplace_back(position, glm::vec3(1.f), color, glm::vec2(0.0f));
		}

		lineModel.bind_Buffer(GL_STATIC_DRAW);
	}

	void create_BoxLines(Mesh& lineModel, float height, float width, float depth, const glm::vec3& color)
	{
		lineModel.Vertices.emplace_back(glm::vec3(width / 2, height / 2, depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));
		lineModel.Vertices.emplace_back(glm::vec3(-width / 2, height / 2, depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));

		lineModel.Vertices.emplace_back(glm::vec3(width / 2, -height / 2, depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));
		lineModel.Vertices.emplace_back(glm::vec3(-width / 2, -height / 2, depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));

		lineModel.Vertices.emplace_back(glm::vec3(width / 2, height / 2, -depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));
		lineModel.Vertices.emplace_back(glm::vec3(-width / 2, height / 2, -depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));

		lineModel.Vertices.emplace_back(glm::vec3(width / 2, -height / 2, -depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));
		lineModel.Vertices.emplace_back(glm::vec3(-width / 2, -height / 2, -depth / 2), glm::vec3(1.f), color, glm::vec2(0.0f));

		lineModel.bind_Buffer(GL_STATIC_DRAW);
	}
}