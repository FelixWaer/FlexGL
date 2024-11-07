#include "GameMap.h"

#include "glad/glad.h"

#include "../Rendering/ModelCreation.h"

#include "Barrel.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"

void GameMap::change_Tile(glm::ivec2& tileCord, uint32_t newTileType)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	newTileType <<= 16;

	GridLayout[gridIndex] |= newTileType;

	change_WallState(tileCord);

	if (gridIndex - GridSize >= 0)
	{
		update_TileState(Bottom, glm::ivec2(tileCord.x, tileCord.y - 1));
	}
	if (gridIndex + 1 < GridLayout.size())
	{
		update_TileState(Left, glm::ivec2(tileCord.x + 1, tileCord.y));
	}
	if (gridIndex + GridSize < GridLayout.size())
	{
		update_TileState(Top, glm::ivec2(tileCord.x, tileCord.y + 1));
	}
	if (gridIndex - 1 >= 0)
	{
		update_TileState(Right, glm::ivec2(tileCord.x - 1, tileCord.y));
	}
}

void GameMap::remove_Tile(glm::ivec2& tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	remove_WallState(tileCord);

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	if (gridIndex - GridSize >= 0)
	{
		remove_TileState(Bottom, glm::ivec2(tileCord.x, tileCord.y - 1));
	}
	if (gridIndex + 1 < GridLayout.size())
	{
		remove_TileState(Left, glm::ivec2(tileCord.x + 1, tileCord.y));
	}
	if (gridIndex + GridSize < GridLayout.size())
	{
		remove_TileState(Top, glm::ivec2(tileCord.x, tileCord.y + 1));
	}
	if (gridIndex - 1 >= 0)
	{
		remove_TileState(Right, glm::ivec2(tileCord.x - 1, tileCord.y));
	}
}

void GameMap::change_TileEdges(glm::ivec2& tileCord, uint32_t direction, uint32_t newTileType, glm::ivec2& neighborTileCord, GameMap* neighborChunk)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	newTileType <<= 16;

	GridLayout[gridIndex] |= newTileType;

	change_WallState(tileCord);

	if (gridIndex - GridSize >= 0)
	{
		update_TileState(Bottom, glm::ivec2(tileCord.x, tileCord.y - 1));
	}
	if (gridIndex + 1 < GridLayout.size())
	{
		update_TileState(Left, glm::ivec2(tileCord.x + 1, tileCord.y));
	}
	if (gridIndex + GridSize < GridLayout.size())
	{
		update_TileState(Top, glm::ivec2(tileCord.x, tileCord.y + 1));
	}
	if (gridIndex - 1 >= 0)
	{
		update_TileState(Right, glm::ivec2(tileCord.x - 1, tileCord.y));
	}

	if (neighborChunk != nullptr)
	{
		neighborTileCord -= neighborChunk->get_ChunkCord() * 32;

		neighborChunk->update_TileState(direction, neighborTileCord);
	}
}

void GameMap::remove_TileEdges(glm::ivec2& tileCord, uint32_t direction, glm::ivec2& neighborTileCord, GameMap* neighborChunk)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	remove_WallState(tileCord);

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	if (gridIndex - GridSize >= 0)
	{
		remove_TileState(Bottom, glm::ivec2(tileCord.x, tileCord.y - 1));
	}
	if (gridIndex + 1 < GridLayout.size())
	{
		remove_TileState(Left, glm::ivec2(tileCord.x + 1, tileCord.y));
	}
	if (gridIndex + GridSize < GridLayout.size())
	{
		remove_TileState(Top, glm::ivec2(tileCord.x, tileCord.y + 1));
	}
	if (gridIndex - 1 >= 0)
	{
		remove_TileState(Right, glm::ivec2(tileCord.x - 1, tileCord.y));
	}

	if (neighborChunk != nullptr)
	{
		neighborTileCord -= neighborChunk->get_ChunkCord() * 32;

		neighborChunk->remove_TileState(direction, neighborTileCord);
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

	if (GridLayout[gridIndex] & Wall || GridLayout[gridIndex] & Item)
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


	GridLayout[gridIndex] |= Wall;

	update_WallState(gridIndex, tileCord);
}

void GameMap::remove_WallState(glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}

	Mesh& gridMesh = EngineManager::get()->get_RenderManager().get_Mesh(ChunkName);

	int gridIndex = tileCord.x + (GridSize * tileCord.y);

	if (GridLayout[gridIndex] & Wall)
	{
		GridLayout[gridIndex] ^= Wall;
		uint32_t resetTexture = 15;
		resetTexture <<= 16;
		GridLayout[gridIndex] ^= resetTexture;
	}

	unsigned int vertexIndex = GridSize * 4 * tileCord.x;
	vertexIndex += 4 * tileCord.y;

	gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.5f, 0.125f);
	gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.5f, 0.0f);
	gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(0.625f, 0.0f);
	gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(0.625f, 0.125f);

	gridMesh.rebind_Buffer(GL_STATIC_DRAW);
}

void GameMap::update_TileState(uint32_t wallDirection, glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}
	uint32_t tileIndex = tileCord.x + (GridSize * tileCord.y);

	wallDirection <<= 8;
	GridLayout[tileIndex] |= wallDirection;

	if (GridLayout[tileIndex] & Wall)
	{
		update_WallState(tileIndex, tileCord);
	}
}

void GameMap::remove_TileState(uint32_t wallDirection, glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= GridSize || tileCord.y >= GridSize)
	{
		return;
	}
	uint32_t tileIndex = tileCord.x + (GridSize * tileCord.y);

	wallDirection <<= 8;
	if (GridLayout[tileIndex] & wallDirection)
	{
		GridLayout[tileIndex] ^= wallDirection;
	}

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
	uint32_t tileType = GridLayout[tileIndex];

	wallState >>= 8;
	wallState &= 15;

	tileType >>= 16;

	if (wallState & Top)
	{
		wallState ^= Top;
	}

	unsigned int vertexIndex = GridSize * 4 * tileCord.x;
	vertexIndex += 4 * tileCord.y;

	float textXPos = 0.f;
	float textYPos = 0.f;
	float textWidth = 0.125f;

	switch (tileType)
	{
	case BrickWall:
		textXPos = 0.0f;
		textYPos = 0.0f;
		break;

	case WoodWall:
		textXPos = 0.0f;
		textYPos = 0.250f;
	default:
		break;
	}

	switch (wallState)
	{
	case SingleWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 2));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 4), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 4), textYPos + (textWidth * 2));
		break;

	case ReverseCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 2));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 0), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 0), textYPos + (textWidth * 2));
		break;

	case VerticalWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 2));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 2));
		break;

	case ReverseInsideCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 0));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 0));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 1));
		break;

	case Corner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 0), textYPos + (textWidth * 2));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 0), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 2));
		break;

	case HorizontalWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 2));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 2));
		break;

	case InsideCorner:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 2), textYPos + (textWidth * 0));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 0));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 1));
		break;

	case MiddleWall:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 1));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 3), textYPos + (textWidth * 0));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 4), textYPos + (textWidth * 0));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 4), textYPos + (textWidth * 1));
		break;

	default:
		gridMesh.Vertices[vertexIndex].Texture = glm::vec2(textXPos + (textWidth * 0), textYPos + (textWidth * 3));
		gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(textXPos + (textWidth * 0), textYPos + (textWidth * 2));
		gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 2));
		gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(textXPos + (textWidth * 1), textYPos + (textWidth * 3));
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
