#include "Graphs.h"
#include "../Engine/EngineManager.h"

void Graphs::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
}

void Graphs::game_Start()
{
	line.init_Model();
	line.bind_ToGameObject(this);
	line.load_Model(FilePathModel);
	line.set_ModelPosition(glm::vec3(10.f, 0.f, 0.f));
	line.turn_OnLine();
}

void Graphs::on_Collision(GameObject* otherGameObject)
{
}
