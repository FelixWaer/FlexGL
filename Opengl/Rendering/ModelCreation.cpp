#include "ModelCreation.h"

#include "Mesh.h"
#include "../Engine/Terrain.h"

float interPolate(float pointA, float pointB, float weight)
{
	//return (pointB - pointA) * weight + pointA;
	return (pointB - pointA) * (3.0 - weight * 2.0) * weight * weight + pointA;
}

glm::vec2 calculate_RandomGradient(int xPos, int yPos)
{
	uint32_t w = 8 * sizeof(uint32_t);
	uint32_t s = w / 2;

	xPos *= 3284157443;
	yPos ^= xPos << s | xPos >> w - s;
	yPos *= 1911520717;
	xPos ^= yPos << s | yPos >> w - s;
	xPos *= 2048419325;

	float random = xPos * (3.14159265 / ~(~0u >> 1));

	glm::vec2 tempVector;
	tempVector.x = cos(random);
	tempVector.y = sin(random);

	return tempVector;
}

float calculate_DotProductGradient(int gridXPos, int gridYPos, float xPos, float yPos)
{
	glm::vec2 gradient = calculate_RandomGradient(gridXPos, gridYPos);

	float xLength = xPos - static_cast<float>(gridXPos);
	float yLength = yPos - static_cast<float>(gridYPos);

	return (xLength * gradient.x + yLength * gradient.y);
}

float calculate_PerlinNoise(float xPos, float zPos)
{
	int gridXPos_1 = static_cast<int>(floor(xPos));
	int gridXPos_2 = gridXPos_1 + 1;
	int gridYPos_1 = static_cast<int>(floor(zPos));
	int gridYPos_2 = gridYPos_1 + 1;

	float interpolateWeight_1 = xPos - static_cast<float>(gridXPos_1);
	float interpolateWeight_2 = zPos - static_cast<float>(gridYPos_1);

	float dot_1 = calculate_DotProductGradient(gridXPos_1, gridYPos_1, xPos, zPos);
	float dot_2 = calculate_DotProductGradient(gridXPos_2, gridYPos_1, xPos, zPos);
	float interpolateDot_1 = interPolate(dot_1, dot_2, interpolateWeight_1);

	dot_1 = calculate_DotProductGradient(gridXPos_1, gridYPos_2, xPos, zPos);
	dot_2 = calculate_DotProductGradient(gridXPos_2, gridYPos_2, xPos, zPos);
	float interpolateDot_2 = interPolate(dot_1, dot_2, interpolateWeight_1);

	return interPolate(interpolateDot_1, interpolateDot_2, interpolateWeight_2);
}

void create_ChunkTerrain(Chunk& chunk)
{
	float stepLength = 0.1f;
	float terrainLength = 3.f;
	float terrainHeight = 50.f;
	uint32_t modelZLength = 0;
	uint32_t modelXLength = 0;
	int64_t chunkXPos = chunk.ChunkPosition.x * 30;
	int64_t chunkZPos = chunk.ChunkPosition.y * 30;

	chunk.ChunkModel = new Model;
	chunk.ChunkModel->create_NewMesh();

	float gridSize = 200.f;

	chunk.ChunkModel->ModelMesh->Vertices.reserve(900);
	for (int64_t xPos = chunkXPos; xPos <= chunkXPos + 30; xPos++)
	{
		modelXLength++;
		for (int64_t zPos = chunkZPos; zPos <= chunkZPos + 30; zPos++)
		{
			float yHeight = 0.f;
			float freq = 2.f;
			float amp = 1.f;
			for (int i = 0; i < 12; i++)
			{
				yHeight += calculate_PerlinNoise(static_cast<float>(xPos) * freq / gridSize, static_cast<float>(zPos) * freq / gridSize) * amp;
				freq *= 1.5f;
				amp *= 0.5f;
			}

			yHeight *= terrainHeight;
			chunk.ChunkModel->ModelMesh->Vertices.emplace_back(glm::vec3(xPos, yHeight, zPos), glm::vec3(0.5f));

			if (xPos == chunkXPos)
			{
				modelZLength++;
			}
		}
	}

	uint32_t rowIndex = 0;

	for (uint32_t i = 0; i < modelXLength - 1; i++)
	{
		for (uint32_t j = 0; j < modelZLength - 1; j++)
		{
			chunk.ChunkModel->ModelMesh->Triangles.emplace_back(rowIndex + j, rowIndex + modelZLength + j, rowIndex + modelZLength + j + 1);
			chunk.ChunkModel->ModelMesh->Triangles.emplace_back(rowIndex + modelZLength + j + 1, rowIndex + j + 1, rowIndex + j);

		}
		rowIndex += modelZLength;
	}

	for (const Triangle& triangle : chunk.ChunkModel->ModelMesh->Triangles)
	{
		calculate_TriangleNormal(chunk.ChunkModel->ModelMesh->Vertices[triangle.FirstIndex],
			chunk.ChunkModel->ModelMesh->Vertices[triangle.ThirdIndex], chunk.ChunkModel->ModelMesh->Vertices[triangle.SecondIndex]);
	}

	chunk.ChunkModel->ModelMesh->bind_Buffer();
}
