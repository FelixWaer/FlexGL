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

	if ((GridLayout[gridIndex - GridSize] & Wall) == Wall)
	{
		change_WallState(glm::ivec2(tileCord.x, tileCord.y - 1));
	}
	if ((GridLayout[gridIndex + 1] & Wall) == Wall)
	{
		change_WallState(glm::ivec2(tileCord.x + 1, tileCord.y));
	}
	if ((GridLayout[gridIndex + GridSize] & Wall) == Wall)
	{
		change_WallState(glm::ivec2(tileCord.x, tileCord.y + 1));
	}
	if ((GridLayout[gridIndex - 1] & Wall) == Wall)
	{
		change_WallState(glm::ivec2(tileCord.x - 1, tileCord.y));
	}
}

void GameMap::change_TileEdges(glm::ivec2& tileCord, GameMap* neighborChunk)
{

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

	if (GridLayout[gridIndex] > 1)
	{
		return true;
	}
	else
	{
		return false;
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

uint32_t GameMap::check_NeighbourTiles(uint32_t tileIndex)
{
	uint32_t result = 0;

	result <<= 1;
	if (GridLayout[tileIndex + 1] & Wall)
	{
		result |= 1;
	}
	result <<= 1;
	if (GridLayout[tileIndex + GridSize] & Wall)
	{
		result |= 1;
	}
	result <<= 1;
	if (GridLayout[tileIndex - 1] & Wall)
	{
		result |= 1;
	}

	return result;
}

void GameMap::change_WallState(glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	Mesh& gridMesh = EngineManager::get()->get_RenderManager().get_Mesh(ChunkName);

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	unsigned int vertexIndex = GridSize * 4 * tileCord.x;
	vertexIndex += 4 * tileCord.y;

	uint32_t WallState = check_NeighbourTiles(gridIndex);

	switch (WallState)
	{
	case SingleWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.60f, 1.0f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.60f, 0.50f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.80f, 0.50f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.80f, 1.0f);
		break;

	case ReverseCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.20f, 1.0f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.20f, 0.5f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.0f, 0.5f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.0f, 1.0f);
		break;

	case VerticalWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.40f, 1.0f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.40f, 0.5f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.60f, 0.5f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.60f, 1.0f);
		break;

	case ReverseInsideCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.60f, 0.5f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.60f, 0.0f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.40f, 0.0f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.40f, 0.5f);
		break;

	case Corner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.0f, 1.0f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.0f, 0.5f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.20f, 0.5f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.20f, 1.0f);
		break;

	case HorizontalWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.20f, 1.0f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.20f, 0.5f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.40f, 0.5f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.40f, 1.0f);
		break;

	case InsideCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.40f, 0.5f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.40f, 0.0f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.60f, 0.0f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.60f, 0.5f);
		break;

	case MiddleWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.60f, 0.5f);
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.60f, 0.0f);
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.80f, 0.0f);
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.80f, 0.5f);
		break;

	default:
		break;
	}

	gridMesh.rebind_Buffer(GL_STATIC_DRAW);
}
