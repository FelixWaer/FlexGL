#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"
#include "../GameObject Components/SphereCollision.h"

class Grid : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;

	void test(glm::ivec2 tileCord);
	void set_TileAsTaken(glm::ivec2 tileCord);
	bool check_IfTileTaken(glm::ivec2 tileCord);

private:
	Model GridModel;
	std::vector<uint32_t> GridLayout;
};

