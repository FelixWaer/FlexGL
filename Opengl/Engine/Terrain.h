#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "../Rendering/Model.h"

struct Chunk
{
	Model* ChunkModel = nullptr;
	glm::ivec2 ChunkPosition = glm::ivec2(0);
};

class Terrain
{
public:
	static Terrain* get_Terrain();
	std::vector<Chunk> Chunks;
	std::vector<Model*> RenderedChunks;

	void set_CurrentChunkPosition(glm::ivec2 currentPosition);
	void generate_Chunk(glm::ivec2 chunkPosition);
	void generate_ChunksAroundChunk(Chunk& chunk);
	void generate_RenderDistanceChunks(glm::ivec2 directionVector, Chunk& chunk);
	uint64_t TotalAmountOfChunks = 0;
private:
	int RenderDistance = 10;
	glm::ivec2 CurrentPosition = glm::ivec2(0);

	inline static Terrain* TheTerrain = nullptr;

	void hide_ChunksOutOfRenderDistance();
};

