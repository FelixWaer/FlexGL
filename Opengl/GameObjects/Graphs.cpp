#include "Graphs.h"

#include "../Engine/EngineManager.h"
#include "../Rendering/Renderer.h"

void Graphs::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
}

void Graphs::game_Start()
{
	PlacableModel.init_Model();
	PlacableModel.bind_ToGameObject(this);
	PlacableModel.set_ModelMesh(&Renderer::get()->TestLoadMesh);
	PlacableModel.set_ModelPosition(glm::vec3(0.f, 0.f, 0.f));
	PlacableModel.scale_Model(glm::vec3(0.05f));
}

void Graphs::on_Collision(GameObject* otherGameObject)
{

}
