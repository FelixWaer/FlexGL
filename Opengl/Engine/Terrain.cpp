#include "Terrain.h"

#include <iostream>

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

void Terrain::generate_Chunk(int64_t chunkXPos, int64_t chunkYPos)
{
	Chunk tempChunk;
	tempChunk.xPos = chunkXPos;
	tempChunk.yPos = chunkYPos;

	create_ChunkTerrain(tempChunk);
	tempChunk.ChunkModel->init_Model();
	tempChunk.ChunkModel->set_ModelPosition(glm::vec3(0.f));
	tempChunk.ChunkModel->scale_Model(glm::vec3(1.f));

	Chunks.emplace_back(tempChunk);
}

void Terrain::generate_ChunksAroundChunk(Chunk& chunk)
{
	int64_t tempXPos = chunk.xPos -2;
	int64_t tempYPos = chunk.yPos -2;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 2 && j == 2)
			{
				tempYPos++;
				continue;
			}
			generate_Chunk(tempXPos, tempYPos);
			tempYPos++;
		}
		tempXPos ++;
		tempYPos -= 5;
	}
}
