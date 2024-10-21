#include "Grid.h"

#include "../Engine/EngineManager.h"
#include "../Rendering/RenderManager.h"
#include "glad/glad.h"

enum BlockState
{
	No_State = 0,
	Ground = 1 << 0,
	Floor = 1 << 1,
	Wall = 1 << 2,

};

void Grid::game_Start()
{
	GridModel.init_Model();
	GridModel.attach_ToGameObject(this);
	//Set the mesh of the Model

	/*Bind the model to a GameObject, so it will move with the GameObject*/
	//testModel.bind_ToGameObject(this);

	//Set position of the Model
	set_GameObjectPosition(glm::vec3(0.f, 0.f, 0.0f));
	GridModel.set_ModelPosition(get_GameObjectPosition());

	//Cube.scale_Model(glm::vec3(10.f, 10.f, 0.f));
	//Cube.rotate_Model(glm::vec3(0.f, 0.f, 0.f));

	//collider.attach_ToGameObject(this);
	//collider.set_SphereRadius(1.f);
	//collider.enable_SphereVisible(true);
	GridModel.set_ModelMesh("Grid");

	GridLayout.resize(100 * 100);
}

void Grid::tick(float deltaTime)
{
}

void Grid::test(glm::ivec2 tileCord)
{
	if (tileCord.x < 0 || tileCord.y < 0 || tileCord.x >= 100 || tileCord.y >= 100)
	{
		return;
	}

	Mesh& gridMesh = EngineManager::get()->get_RenderManager().get_Mesh("Grid");

	unsigned int vertexIndex = 100 * 4 * tileCord.x;
	vertexIndex += 4 * tileCord.y;
	gridMesh.Vertices[vertexIndex].Texture = glm::vec2(0.f, 1.f);
	gridMesh.Vertices[vertexIndex + 1].Texture = glm::vec2(0.f, 0.f);
	gridMesh.Vertices[vertexIndex + 2].Texture = glm::vec2(1.f, 0.f);
	gridMesh.Vertices[vertexIndex + 3].Texture = glm::vec2(1.f, 1.f);

	gridMesh.rebind_Buffer(GL_STATIC_DRAW);

	int gridIndex = tileCord.x + (100 * tileCord.y);

	GridLayout[gridIndex] = 1;
}

void Grid::set_TileAsTaken(glm::ivec2 tileCord)
{
	int gridIndex = tileCord.x + (100 * tileCord.y);

	GridLayout[gridIndex] = 1;
}

bool Grid::check_IfTileTaken(glm::ivec2 tileCord)
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
