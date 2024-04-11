#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "../Rendering/Model.h"

struct Chunk
{
	Model* ChunkModel = nullptr;
	int64_t xPos = 0;
	int64_t yPos = 0;
};

class Terrain
{
public:
	static Terrain* get_Terrain();
	std::vector<Chunk> Chunks;

	void generate_Chunk(int64_t chunkXPos, int64_t chunkYPos);
	void generate_ChunksAroundChunk(Chunk& chunk);
private:

	inline static Terrain* TheTerrain = nullptr;
};

