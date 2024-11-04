#include "Enemy.h"

#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/TagComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/DamageComponent.h"
#include "../Components/CollisionComponent.h"

void Enemy::init_Entity()
{
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<TransformComponent>();
	add_Component<SpriteComponent>();
	add_Component<TagComponent>();
	add_Component<HealthComponent>();
	add_Component<DamageComponent>();
	add_Component<CollisionComponent>();

	get_Component<MovementComponent>().Speed = 50.f;
	get_Component<TagComponent>().Tag = "Enemy";
	get_Component<HealthComponent>().Health = 20.f;
	get_Component<DamageComponent>().Damage = 20.f;
	get_Component<DamageComponent>().CooldownTimer = 3.f;
	get_Component<CollisionComponent>().Radius = 128.f;
	get_Component<SpriteComponent>().MaterialName = "EnemyMaterial";
	TransformComponent& transComp = get_Component<TransformComponent>();
	transComp.Rotation = glm::vec3(0.f);
	transComp.Scale = glm::vec3(32.f, 32.f, 0.f);
}
