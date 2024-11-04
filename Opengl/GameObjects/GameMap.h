#pragma once
#include "Entity.h"

class GameMap : public Entity
{
public:
	void change_Tile(glm::ivec2& tileCord);
	void change_TileEdges(glm::ivec2& tileCord, GameMap* neighborChunk);

	void set_TileAsTaken(glm::ivec2 tileCord);
	bool check_IfTileTaken(glm::ivec2 tileCord);
	glm::ivec2& get_ChunkCord();
	void set_ChunkCord(glm::ivec2 newChunkCord);
protected:
	void init_Entity() override;

private:
	int GridSize = 32;
	std::string ChunkName;
	glm::ivec2 ChunkCord = glm::ivec2(0.f);
	std::vector<uint32_t> GridLayout = std::vector<uint32_t>(GridSize*GridSize, 1);

	uint32_t check_NeighbourTiles(uint32_t tileIndex);
	void change_WallState(glm::ivec2 tileCord);
};

