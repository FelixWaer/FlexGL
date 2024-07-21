#pragma once
#include <glm/glm.hpp>

struct Vertex
{
	Vertex() = default;
	Vertex(const glm::vec3& position, const glm::vec3& color) :
		Position(position), Color(color) {}
	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& color, const glm::vec2& texCord) :
		Position(position), Normal(normal), Color(color), Texture(texCord) {}

	bool operator==(const Vertex& other) const
	{
		return Position == other.Position && Color == other.Color && Texture == other.Texture && Normal == other.Normal;
	}

	glm::vec3 Position = glm::vec3(0.f);
	glm::vec3 Normal = glm::vec3(0.f);
	glm::vec3 Color = glm::vec3(0.f);
	glm::vec2 Texture = glm::vec2(0.f);
};

struct Triangle
{
	Triangle() = default;
	Triangle(unsigned int firstIndex, unsigned int secondIndex, unsigned int thirdIndex) :
		FirstIndex(firstIndex), SecondIndex(secondIndex), ThirdIndex(thirdIndex) {}

	unsigned int FirstIndex;
	unsigned int SecondIndex;
	unsigned int ThirdIndex;
};