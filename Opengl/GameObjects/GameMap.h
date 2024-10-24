#pragma once
#include "Entity.h"

class GameMap : public Entity
{
public:
	void test(glm::ivec2 tileCord);
	void set_TileAsTaken(glm::ivec2 tileCord);
	bool check_IfTileTaken(glm::ivec2 tileCord);

protected:
	void init_Entity() override;

private:
	std::vector<uint32_t> GridLayout = std::vector<uint32_t>(100*100, 1);

	uint32_t check_NeighbourTiles(uint32_t tileIndex);
	void change_WallState(glm::ivec2 tileCord);
};

