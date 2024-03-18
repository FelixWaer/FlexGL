#include "Box.h"

#include "../Model.h"

void Box::game_Start()
{
	BoxModel.init_Model();
	BoxModel.bind_ToGameObject(this);
	create_Cube(BoxModel, glm::vec3(0.f, 0.f, 1.f));
	BoxModel.scale_Model(glm::vec3(10.f, 1.f, 10.f));

	set_GameObjectPosition(glm::vec3(-40.f, 0.f, -40.f));

	BoxCollider.attach_ToGameObject(this);
	BoxCollider.enable_BoxVisible(true);
	BoxCollider.set_BoxWidth(10.1f);
	BoxCollider.set_BoxHeight(1.1f);
	BoxCollider.set_BoxDepth(10.1f);
	add_Tag("Box");
}

void Box::on_Collision(GameObject* otherGameObject)
{
	glm::vec3 direction = get_GameObjectPosition() - otherGameObject->get_GameObjectPosition();

	if (get_GameObjectPosition().x <= get_GameObjectPosition().x + 10.f && get_GameObjectPosition().x >= get_GameObjectPosition().x - 10.f)
	{
		otherGameObject->get_GameObjectVelocity().x = 0;
	}
	if (get_GameObjectPosition().y <= get_GameObjectPosition().y + 1.f && get_GameObjectPosition().y >= get_GameObjectPosition().y - 1.0f)
	{
		otherGameObject->get_GameObjectVelocity().y = 0;
	}
	if (get_GameObjectPosition().z <= get_GameObjectPosition().z + 10.f && get_GameObjectPosition().z >= get_GameObjectPosition().z - 10.f)
	{
		otherGameObject->get_GameObjectVelocity().z = 0;
	}
}
