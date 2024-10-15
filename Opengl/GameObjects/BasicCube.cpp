#include "BasicCube.h"

void BasicCube::game_Start()
{
	//Initialize the Model -MUST BE DONE
	Cube.init_Model();
	Cube.attach_ToGameObject(this);
	//Set the mesh of the Model

	/*Bind the model to a GameObject, so it will move with the GameObject*/
	//testModel.bind_ToGameObject(this);

	//Set position of the Model
	Cube.set_ModelPosition(get_GameObjectPosition());
	Cube.scale_Model(glm::vec3(64.f, 64.f, 0.f));

	//Cube.scale_Model(glm::vec3(10.f, 10.f, 0.f));
	//Cube.rotate_Model(glm::vec3(0.f, 0.f, 0.f));

	//collider.attach_ToGameObject(this);
	//collider.set_SphereRadius(1.f);
	//collider.enable_SphereVisible(true);
	Cube.set_ModelMesh("Square");
	Cube.set_ModelMaterial("ObjectMaterial");
	add_Tag("BasicCube");
	//set_GameObjectVelocity(glm::vec3(1.f, 0.f, 0.f));
}

void BasicCube::tick(float deltaTime)
{
	GameObject::tick(deltaTime);

	//set_GameObjectPosition(glm::vec3(0.f));
}
