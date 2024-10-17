#include "GameMap.h"

#include "glad/glad.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

void GameMap::test(glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= 100 || tileCord.y >= 100)
	{
		return;
	}

	Mesh& gridMesh = EngineManager::get()->get_RenderManager().get_Mesh("Grid");

	unsigned int vertexIndex = 100 * 4 * tileCord.x;
	vertexIndex += 4 * tileCord.y;
	gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.0f, 1.f);
	gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.0f, 0.f);
	gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.5f, 0.f);
	gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.5f, 1.f);

	gridMesh.rebind_Buffer(GL_STATIC_DRAW);

	int gridIndex = tileCord.x + (100 * tileCord.y);

	GridLayout[gridIndex] = 1;
}

void GameMap::set_TileAsTaken(glm::ivec2 tileCord)
{
	int gridIndex = tileCord.x + (100 * tileCord.y);

	GridLayout[gridIndex] = 1;
}

bool GameMap::check_IfTileTaken(glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= 100 || tileCord.y >= 100)
	{
		return true;
	}

	int gridIndex = tileCord.x + (100 * tileCord.y);

	if (GridLayout[gridIndex] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameMap::init_Entity()
{
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<TransformComponent>();
	add_Component<SpriteComponent>();

	get_Component<SpriteComponent>().MaterialName = "BasicMaterial";
	get_Component<SpriteComponent>().SpriteName = "Grid";

	GridLayout.resize(100 * 100);
}
