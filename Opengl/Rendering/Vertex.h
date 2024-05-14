#pragma once
#include <glm/glm.hpp>

struct VertexTest
{
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 Texture;
	glm::vec3 Normal;

	
	bool operator==(const VertexTest& other) const
	{
		return Position == other.Position && Color == other.Color && Texture == other.Texture && Normal == other.Normal;
	}
};

