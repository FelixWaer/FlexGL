#include "BasicCube.h"

#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Engine/SceneManager.h"

void BasicCube::game_Start()
{
	////Initialize the Model -MUST BE DONE
	//Cube.init_Model();
	//Cube.attach_ToGameObject(this);
	////Set the mesh of the Model

	///*Bind the model to a GameObject, so it will move with the GameObject*/
	////testModel.bind_ToGameObject(this);

	////Set position of the Model
	//Cube.set_ModelPosition(get_GameObjectPosition());
	//Cube.scale_Model(glm::vec3(64.f, 64.f, 0.f));

	////Cube.scale_Model(glm::vec3(10.f, 10.f, 0.f));
	////Cube.rotate_Model(glm::vec3(0.f, 0.f, 0.f));

	////collider.attach_ToGameObject(this);
	////collider.set_SphereRadius(1.f);
	////collider.enable_SphereVisible(true);
	//Cube.set_ModelMesh("Square");
	//add_Tag("BasicCube");
}

void BasicCube::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
}

void BasicCube::init_Entity()
{
	ParentScene->get_ComponentManager().add_Component<PositionComponent>(get_GameObjectID());
	ParentScene->get_ComponentManager().add_Component<MovementComponent>(get_GameObjectID());
	ParentScene->get_ComponentManager().add_Component<TransformComponent>(get_GameObjectID());
	ParentScene->get_ComponentManager().add_Component<SpriteComponent>(get_GameObjectID());

	ParentScene->get_ComponentManager().get_Component<PositionComponent>(get_GameObjectID()).Position = get_GameObjectPosition();
	TransformComponent& transComp = ParentScene->get_ComponentManager().get_Component<TransformComponent>(get_GameObjectID());
	transComp.Rotation = glm::vec3(0.f);
	transComp.Scale = glm::vec3(64.f, 64.f, 0.f);
}

void BasicCube::update_Position(glm::vec3 newPosition)
{

	set_GameObjectPosition(newPosition);
	//Cube.set_ModelPosition(get_GameObjectPosition());
	ParentScene->get_ComponentManager().get_Component<PositionComponent>(get_GameObjectID()).Position = newPosition;
}

void BasicCube::set_Material(std::string materialName)
{
	ParentScene->get_ComponentManager().get_Component<SpriteComponent>(get_GameObjectID()).MaterialName = materialName;
}
