#include "Terrain.h"

#include <iostream>

#include "../Rendering/Mesh.h"
#include "../Rendering/ModelCreation.h"

Terrain* Terrain::get_Terrain()
{
	if (TheTerrain == nullptr)
	{
		TheTerrain = new Terrain;
		return TheTerrain;
	}
	return TheTerrain;
}

void Terrain::set_CurrentChunkPosition(glm::ivec2 currentPosition)
{
	CurrentPosition = currentPosition;
}

void Terrain::generate_Chunk(glm::ivec2 chunkPosition)
{
	for (Chunk chunk : Chunks)
	{
		if (chunk.ChunkPosition == chunkPosition)
		{
			chunk.ChunkModel->hide_Model(false);
			return;
		}
	}

	Chunk tempChunk;
	tempChunk.ChunkPosition = chunkPosition;

	create_ChunkTerrain(tempChunk);
	tempChunk.ChunkModel->init_Model();
	tempChunk.ChunkModel->set_ModelPosition(glm::vec3(0.f));
	tempChunk.ChunkModel->scale_Model(glm::vec3(1.f));

	Chunks.emplace_back(tempChunk);

	TotalAmountOfChunks++;
}

void Terrain::generate_ChunksAroundChunk(Chunk& chunk)
{
	glm::ivec2 tempVec(chunk.ChunkPosition-2);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
		/*	if (i == 2 && j == 2)
			{
				tempVec.y++;
				continue;
			}*/
			generate_Chunk(tempVec);
			tempVec.y++;
		}
		tempVec.x++;
		tempVec.y -= 5;
	}
}

void Terrain::generate_RenderDistanceChunks(glm::ivec2 directionVector)
{
	CurrentPosition += directionVector;
	glm::ivec2 reverseDirection(0);
	reverseDirection.x = directionVector.y;
	reverseDirection.y = directionVector.x;
	glm::ivec2 tempVec2 = reverseDirection;
	directionVector *= 2;
	reverseDirection *= 2;

	if (reverseDirection.x > 0 || reverseDirection.y > 0)
	{
		reverseDirection *= -1;
	}
	if (tempVec2.x < 0 || tempVec2.y < 0)
	{
		tempVec2 *= -1;
	}

	for (int i = 0; i < 5; i++)
	{
		generate_Chunk((CurrentPosition + directionVector + reverseDirection) + (tempVec2 * i));
		for (Chunk chunk : Chunks)
		{
			if (directionVector.x < 0 || directionVector.y < 0)
			{
				if (chunk.ChunkPosition == (CurrentPosition + directionVector + reverseDirection) + (tempVec2 * i) + directionVector * 5)
				{
					chunk.ChunkModel->hide_Model(true);
					return;
				}
			}
			if (chunk.ChunkPosition == (CurrentPosition + directionVector + reverseDirection) + (tempVec2 * i) + directionVector * -5)
			{
				chunk.ChunkModel->hide_Model(true);
				return;
			}
		}
	}
}