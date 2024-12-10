#include "Cube.h"

#include "../Components/MovementComponent.h"
#include "../Components/ParticleComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/SphereCollComponent.h"
#include "..\Components\MeshComponent.h"
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
	add_Component<MeshComponent>();
	add_Component<TransformComponent>();
	add_Component<ParticleComponent>();
	add_Component<SphereCollComponent>();
	add_Component<TagComponent>();
	add_Component<PhysicsComponent>();
	add_Component<ScriptComponent>();

	get_Component<PositionComponent>().Position = glm::vec3(0.f, 20.f, 10.f);
	get_Component<MeshComponent>().MaterialName = "BasicMaterial";
	get_Component<MeshComponent>().MeshName = "Cube";
	get_Component<MeshComponent>().Render = true;

	get_Component<ParticleComponent>().Radius = 25.f;
	get_Component<ParticleComponent>().MaxParticleCount = 5000.f;
	get_Component<ParticleComponent>().MaxLifeTime = 5.f;
	get_Component<ParticleComponent>().ParticleSpeed = 5.f;
	get_Component<ParticleComponent>().SpawnInterval = 0.01f;
	get_Component<ParticleComponent>().Direction = glm::vec3(0.f, -1.f, 0.f);

	get_Component<SphereCollComponent>().Radius = 0.5f;
	get_Component<TagComponent>().Tag = "Cube";
	get_Component<ScriptComponent>().ScriptPath = "Scripts/Cube.Lua";

	enable_Ticking();
}
