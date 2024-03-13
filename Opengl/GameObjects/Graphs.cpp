#include "Graphs.h"
#include "../EngineManager.h"

void Graphs::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
}

void Graphs::game_Start()
{
	line.init_LineModel();
	line.bind_ToGameObject(this);
	line.load_LineModel(FilePathModel);
	line.set_Location(glm::vec3(10.f, 0.f, 0.f));
}

void Graphs::on_Collision(GameObject* otherGameObject)
{
}
