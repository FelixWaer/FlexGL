#pragma once
#include "../GameObject.h"
#include "../Model.h"
#include "../GameObject Components/SphereCollision.h"

class Graphs : public GameObject
{
public:
	void tick(float deltaTime) override;
	void game_Start() override;
	void on_Collision(GameObject* otherGameObject) override;

private:
	Line line = Line(true);
	std::string FilePathModel = "Models/Data Points Interpolation";
};

