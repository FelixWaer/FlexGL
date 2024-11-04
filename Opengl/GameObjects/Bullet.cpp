#include "Bullet.h"

#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/DamageComponent.h"
#include "../Components/CollisionComponent.h"

void Bullet::init_Entity()
{
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<TransformComponent>();
	add_Component<SpriteComponent>();
	add_Component<TagComponent>();
	add_Component<HealthComponent>();
	add_Component<DamageComponent>();
	add_Component<CollisionComponent>();

	get_Component<MovementComponent>().Speed = 100.f;
	get_Component<TagComponent>().Tag = "Bullet";
	get_Component<HealthComponent>().Health = 100.f;
	get_Component<DamageComponent>().Damage = 20.f;
	get_Component<DamageComponent>().CooldownTimer = 0.5f;
	get_Component<CollisionComponent>().Radius = 32.f;
	get_Component<SpriteComponent>().MaterialName = "BulletMaterial";
	TransformComponent& transComp = get_Component<TransformComponent>();
	transComp.Rotation = glm::vec3(0.f);
	transComp.Scale = glm::vec3(16.f, 16.f, 0.f);
}
