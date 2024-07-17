#include "BasicCube.h"

#include "../Rendering/Renderer.h"

void BasicCube::game_Start()
{
	//Initialize the Model -MUST BE DONE
	Cube.init_Model();

	//Set the mesh of the Model
	Cube.set_ModelMesh(&Renderer::get()->Cube);

	/*Bind the model to a GameObject, so it will move with the GameObject*/
	//testModel.bind_ToGameObject(this);

	//Set position of the Model
	Cube.set_ModelPosition(glm::vec3(0.f));

	//collider.attach_ToGameObject(this);
	//collider.set_SphereRadius(1.f);
	//collider.enable_SphereVisible(true);

	add_Tag("BasicCube");
}

void BasicCube::tick(float deltaTime)
{
}
