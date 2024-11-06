#pragma once
#include "Entity.h"

enum TileState
{
	Null_State = 0,
	Water = 1 << 0,
	Ground = 1 << 1,
	Floor = 1 << 2,
	Wall = 1 << 3,
	Item = 1 << 4,
};

enum WallState
{
	SingleWall = 0,
	ReverseCorner = 1,
	VerticalWall = 2,
	ReverseInsideCorner = 3,
	Corner = 4,
	HorizontalWall = 5,
	InsideCorner = 6,
	MiddleWall = 7,
};

enum Direction
{
	Left = 1 << 0,
	Bottom = 1 << 1,
	Right = 1 << 2,
	Top = 1 << 3,
};

class GameMap : public Entity
{
public:
	void change_Tile(glm::ivec2& tileCord);
	void remove_Tile(glm::ivec2& tileCord);
	void change_TileEdges(glm::ivec2& tileCord, uint32_t direction, glm::ivec2& neighborTileCord, GameMap* neighborChunk);
	void remove_TileEdges(glm::ivec2& tileCord, uint32_t direction, glm::ivec2& neighborTileCord, GameMap* neighborChunk);

	void set_TileAsTaken(glm::ivec2 tileCord);
	bool check_IfTileTaken(glm::ivec2 tileCord);
	void change_WallState(glm::ivec2 tileCord);
	void remove_WallState(glm::ivec2 tileCord);
	void update_TileState(uint32_t wallDirection, glm::ivec2 tileCord);
	void remove_TileState(uint32_t wallDirection, glm::ivec2 tileCord);
	glm::ivec2& get_ChunkCord();
	void set_ChunkCord(glm::ivec2 newChunkCord);
protected:
	void init_Entity() override;

private:
	int GridSize = 32;
	std::string ChunkName;
	glm::ivec2 ChunkCord = glm::ivec2(0.f);
	std::vector<uint32_t> GridLayout = std::vector<uint32_t>(GridSize*GridSize, 1);

	void update_WallState(uint32_t tileIndex, glm::ivec2& tileCord);
	uint32_t check_NeighbourTiles(int tileIndex);
};

