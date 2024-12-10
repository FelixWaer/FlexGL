#include "Cube.h"

#include "../Components/MovementComponent.h"
#include "../Components/ParticleComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SphereCollComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/TransformComponent.h"

void Cube::tick(float deltaTime)
{
	if (testEntity != nullptr)
	{
		get_Component<TransformComponent>().Rotation += glm::vec3(0.f, 1.f, 1.f) * deltaTime;
		testEntity->get_Component<TransformComponent>().Matrix = get_Component<TransformComponent>().Matrix * testEntity->get_Component<TransformComponent>().Matrix;
	}
}

void Cube::init_Entity()
{
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<SpriteComponent>();
	add_Component<TransformComponent>();
	add_Component<ParticleComponent>();
	add_Component<SphereCollComponent>();
	add_Component<TagComponent>();
	add_Component<PhysicsComponent>();

	get_Component<PositionComponent>().Position = glm::vec3(0.f, 20.f, 10.f);
	get_Component<SpriteComponent>().MaterialName = "BasicMaterial";
	get_Component<SpriteComponent>().SpriteName = "Cube";
	get_Component<SpriteComponent>().Render = true;

	get_Component<ParticleComponent>().Radius = 10.f;
	get_Component<ParticleComponent>().MaxParticleCount = 1000.f;
	get_Component<ParticleComponent>().MaxLifeTime = 5.f;
	get_Component<ParticleComponent>().ParticleSpeed = 5.f;
	get_Component<ParticleComponent>().SpawnInterval = 0.01f;
	get_Component<ParticleComponent>().Direction = glm::vec3(0.f, -1.f, 0.f);

	get_Component<SphereCollComponent>().Radius = 1.f;
	get_Component<TagComponent>().Tag = "Cube";

	enable_Ticking();
}
