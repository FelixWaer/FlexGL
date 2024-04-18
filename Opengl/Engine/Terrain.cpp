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
			RenderedChunks.emplace_back(chunk.ChunkModel);
			return;
		}
	}

	Chunk tempChunk;
	tempChunk.ChunkPosition = chunkPosition;

	create_ChunkTerrain(tempChunk);
	//tempChunk.ChunkModel->init_Model();
	tempChunk.ChunkModel->set_ModelPosition(glm::vec3(0.f));
	tempChunk.ChunkModel->scale_Model(glm::vec3(1.f));

	Chunks.emplace_back(tempChunk);
	RenderedChunks.emplace_back(tempChunk.ChunkModel);

	TotalAmountOfChunks++;
}

void Terrain::generate_ChunksAroundChunk(Chunk& chunk)
{
	glm::ivec2 tempVec(chunk.ChunkPosition-RenderDistance);

	for (int i = 0; i < (RenderDistance*2)+1; i++)
	{
		for (int j = 0; j < (RenderDistance*2)+1; j++)
		{
			generate_Chunk(tempVec);
			tempVec.y++;
		}
		tempVec.x++;
		tempVec.y -= (RenderDistance * 2) + 1;
	}
}

void Terrain::generate_RenderDistanceChunks(glm::ivec2 directionVector, Chunk& chunk)
{
	hide_ChunksOutOfRenderDistance();
	generate_ChunksAroundChunk(chunk);

	//CurrentPosition += directionVector;
	//glm::ivec2 reverseDirection(0);
	//reverseDirection.x = directionVector.y;
	//reverseDirection.y = directionVector.x;
	//glm::ivec2 tempVec2 = reverseDirection;
	//directionVector *= 2;
	//reverseDirection *= 2;

	//if (reverseDirection.x > 0 || reverseDirection.y > 0)
	//{
	//	reverseDirection *= -1;
	//}
	//if (tempVec2.x < 0 || tempVec2.y < 0)
	//{
	//	tempVec2 *= -1;
	//}
	//for (int i = 0; i < 5; i++)
	//{
	//	//generate_Chunk((CurrentPosition + directionVector + reverseDirection) + (tempVec2 * i));
	//	//for (Chunk chunk : Chunks)
	//	//{
	//	//	if (directionVector.x < 0 || directionVector.y < 0)
	//	//	{
	//	//		if (chunk.ChunkPosition == (CurrentPosition + directionVector + reverseDirection) + (tempVec2 * i) + directionVector * 5)
	//	//		{
	//	//			chunk.ChunkModel->hide_Model(true);
	//	//			return;
	//	//		}
	//	//	}
	//	//	if (chunk.ChunkPosition == (CurrentPosition + directionVector + reverseDirection) + (tempVec2 * i) + directionVector * -5)
	//	//	{
	//	//		chunk.ChunkModel->hide_Model(true);
	//	//		return;
	//	//	}
	//	//}
	//}
}

void Terrain::hide_ChunksOutOfRenderDistance()
{
	for (Model* chunkModel : RenderedChunks)
	{
		chunkModel->hide_Model(true);
		chunkModel = nullptr;
	}
	RenderedChunks.clear();
	int TotalChunksRendered = (RenderDistance * 2) + 1;
	RenderedChunks.reserve(TotalChunksRendered*TotalChunksRendered);
}
