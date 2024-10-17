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
	std::vector<int> GridLayout;
};

