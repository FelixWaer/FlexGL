#include "GameMap.h"

#include "glad/glad.h"

#include "../Rendering/ModelCreation.h"

#include "Barrel.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

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

void GameMap::change_Tile(glm::ivec2& tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	change_WallState(tileCord);

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	GridLayout[gridIndex] |= Wall;

	if (gridIndex - GridSize >= 0)
	{
		if ((GridLayout[gridIndex - GridSize] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x, tileCord.y - 1));
		}
	}
	if (gridIndex + 1 < GridLayout.size())
	{
		if ((GridLayout[gridIndex + 1] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x + 1, tileCord.y));
		}
	}
	if (gridIndex + GridSize < GridLayout.size())
	{
		if ((GridLayout[gridIndex + GridSize] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x, tileCord.y + 1));
		}
	}
	if (gridIndex - 1 >= 0)
	{
		if ((GridLayout[gridIndex - 1] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x - 1, tileCord.y));
		}
	}
}

void GameMap::change_TileEdges(glm::ivec2& tileCord, glm::ivec2& neighborTileCord, GameMap* neighborChunk)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}
	std::cout << "I am wall! " << std::endl;
	change_WallState(tileCord);

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	if (gridIndex - GridSize >= 0)
	{
		if ((GridLayout[gridIndex - GridSize] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x, tileCord.y - 1));
		}
	}
	if (gridIndex + 1 < GridLayout.size())
	{
		if ((GridLayout[gridIndex + 1] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x + 1, tileCord.y));
		}
	}
	if (gridIndex + GridSize < GridLayout.size())
	{
		if ((GridLayout[gridIndex + GridSize] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x, tileCord.y + 1));
		}
	}
	if (gridIndex - 1 >= 0)
	{
		if ((GridLayout[gridIndex - 1] & Wall) == Wall)
		{
			change_WallState(glm::ivec2(tileCord.x - 1, tileCord.y));
		}
	}

	if (neighborChunk != nullptr)
	{
		neighborTileCord -= neighborChunk->get_ChunkCord() * 32;
		uint32_t test = 2;
		neighborChunk->update_TileState(test, neighborTileCord);
	}
}

void GameMap::set_TileAsTaken(glm::ivec2 tileCord)
{
	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	GridLayout[gridIndex] |= Item;
}

bool GameMap::check_IfTileTaken(glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return true;
	}

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	if (GridLayout[gridIndex] & Wall)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameMap::change_WallState(glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	uint32_t wallState = check_NeighbourTiles(gridIndex);

	GridLayout[gridIndex] |= Wall;

	update_TileState(wallState, tileCord);
}

void GameMap::update_TileState(uint32_t newWallState, glm::ivec2& tileCord)
{
	uint32_t tileIndex = tileCord.x + (GridSize * tileCord.y);

	newWallState <<= 4;
	GridLayout[tileIndex] |= newWallState;

	if (GridLayout[tileIndex] & Wall)
	{
		update_WallState(tileIndex, tileCord);
	}
}

glm::ivec2& GameMap::get_ChunkCord()
{
	return ChunkCord;
}

void GameMap::set_ChunkCord(glm::ivec2 newChunkCord)
{
	ChunkCord = newChunkCord;
	int xPos = ChunkCord.x << 11;
	int yPos = ChunkCord.y << 11;
	get_Component<PositionComponent>().Position = glm::vec3(xPos, yPos, 0.f);
}

void GameMap::init_Entity()
{
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<TransformComponent>();
	add_Component<SpriteComponent>();

	Mesh tempMesh;
	std::string meshName = "Chunk" + std::to_string(get_EntityID());
	FLXModel::create_Grid(tempMesh, 32);
	ChunkName = meshName;

	EngineManager::get()->get_RenderManager().add_Mesh(tempMesh, meshName);
	get_Component<SpriteComponent>().MaterialName = "BasicMaterial";
	get_Component<SpriteComponent>().SpriteName = meshName;
}

void GameMap::update_WallState(uint32_t tileIndex, glm::ivec2& tileCord)
{
	Mesh& gridMesh = EngineManager::get()->get_RenderManager().get_Mesh(ChunkName);

	uint32_t wallState = GridLayout[tileIndex];

	wallState >>= 4;

	unsigned int vertexIndex = GridSize * 4 * tileCord.x;
	vertexIndex += 4 * tileCord.y;

	switch (wallState)
	{
	case SingleWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.375f, 0.250f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.375f, 0.125f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.500f, 0.125f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.500f, 0.250f);
		break;

	case ReverseCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.125f, 0.250f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.125f, 0.125f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.0f, 0.125f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.0f, 0.250f);
		break;

	case VerticalWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.250f, 0.250f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.250f, 0.125f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.375f, 0.125f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.375f, 0.250f);
		break;

	case ReverseInsideCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.375f, 0.125f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.375f, 0.0f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.250f, 0.0f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.250f, 0.125f);
		break;

	case Corner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.0f, 0.250f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.0f, 0.125f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.125f, 0.125f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.125f, 0.250f);
		break;

	case HorizontalWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.125f, 0.250f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.125f, 0.125f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.250f, 0.125f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.250f, 0.250f);
		break;

	case InsideCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.250f, 0.125f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.250f, 0.0f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.375f, 0.0f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.375f, 0.125f);
		break;

	case MiddleWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.375f, 0.125f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.375f, 0.0f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.500f, 0.0f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.500f, 0.125f);
		break;

	default:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.0f, 0.375f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.0f, 0.250f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.125f, 0.250f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.125f, 0.375f);
		break;
	}

	gridMesh.rebind_Buffer(GL_STATIC_DRAW);
}

uint32_t GameMap::check_NeighbourTiles(int tileIndex)
{
	uint32_t result = 0;

	result <<= 1;
	if (tileIndex + 1 < GridLayout.size())
	{
		if (GridLayout[tileIndex + 1] & Wall)
		{
			result |= 1;
		}
	}
	result <<= 1;

	if (tileIndex + GridSize < GridLayout.size())
	{
		if (GridLayout[tileIndex + GridSize] & Wall)
		{
			result |= 1;
		}
	}
	result <<= 1;

	if (tileIndex - 1 >= 0)
	{
		if (GridLayout[tileIndex - 1] & Wall)
		{
			result |= 1;
		}
	}

	return result;
}
