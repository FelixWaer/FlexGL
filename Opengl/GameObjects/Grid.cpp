#include "Grid.h"

#include "../Engine/EngineManager.h"
#include "../Rendering/RenderManager.h"
#include "glad/glad.h"

void Grid::game_Start()
{
	GridModel.init_Model();
	GridModel.attach_ToGameObject(this);
	//Set the mesh of the Model

	/*Bind the model to a GameObject, so it will move with the GameObject*/
	//testModel.bind_ToGameObject(this);

	//Set position of the Model
	GridModel.set_ModelPosition(get_GameObjectPosition());

	//Cube.scale_Model(glm::vec3(10.f, 10.f, 0.f));
	//Cube.rotate_Model(glm::vec3(0.f, 0.f, 0.f));

	//collider.attach_ToGameObject(this);
	//collider.set_SphereRadius(1.f);
	//collider.enable_SphereVisible(true);
	GridModel.set_ModelMesh("Grid");
}

void Grid::tick(float deltaTime)
{
}

void Grid::test(glm::ivec2 tileCord)
{
	Mesh& gridMesh = EngineManager::get()->get_RenderManager().get_Mesh("Grid");

	unsigned int vertexIndex = 100 * 4 * tileCord.x;
	vertexIndex += 4 * tileCord.y;
	gridMesh.Vertices[vertexIndex].Color = glm::vec3(0.f);
	gridMesh.Vertices[vertexIndex + 1].Color = glm::vec3(0.f);
	gridMesh.Vertices[vertexIndex + 2].Color = glm::vec3(0.f);
	gridMesh.Vertices[vertexIndex + 3].Color = glm::vec3(0.f);

	gridMesh.bind_Buffer(GL_STATIC_DRAW);
	std::cout << vertexIndex << std::endl;
}
