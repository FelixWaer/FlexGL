#include "Barrel.h"

#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/TagComponent.h"

void Barrel::init_Entity()
{
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<TransformComponent>();
	add_Component<SpriteComponent>();
	add_Component<TagComponent>();

	get_Component<TagComponent>().Tag = "Barrel";
	get_Component<SpriteComponent>().MaterialName = "ObjectMaterial";
	TransformComponent& transComp = get_Component<TransformComponent>();
	transComp.Rotation = glm::vec3(0.f);
	transComp.Scale = glm::vec3(64.f, 64.f, 0.f);
}
