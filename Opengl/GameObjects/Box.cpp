#include "Box.h"

#include "../Rendering/Model.h"
#include "../Rendering/Renderer.h"

void Box::game_Start()
{
	BoxModel.init_Model();
	BoxModel.bind_ToGameObject(this);
	BoxModel.set_ModelMesh(&Renderer::get()->Cube);
	BoxModel.scale_Model(glm::vec3(50.f, 1.f, 50.f));

	set_GameObjectPosition(glm::vec3(25.f, -2.f, 25.f));

	BoxCollider.attach_ToGameObject(this);
	BoxCollider.enable_BoxVisible(true);
	BoxCollider.set_BoxWidth(50.f);
	BoxCollider.set_BoxHeight(1.1f);
	BoxCollider.set_BoxDepth(50.f);
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
