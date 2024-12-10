#include "Floor.h"

#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "..\Components\MeshComponent.h"
#include "../Components/TransformComponent.h"

void Floor::init_Entity()
{
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<MeshComponent>();
	add_Component<TransformComponent>();

	get_Component<PositionComponent>().Position = glm::vec3(0.f);
	get_Component<MeshComponent>().MaterialName = "BasicMaterial";
	get_Component<MeshComponent>().MeshName = "Cube";
	get_Component<TransformComponent>().Scale = glm::vec3(50.f, 1.f, 50.f);
}
