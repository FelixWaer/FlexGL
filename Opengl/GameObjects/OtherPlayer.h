#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Model.h"

#include "../Engine/FlexClient Code/FlexClient.h"

class OtherPlayer : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;
	void on_Collision(GameObject* otherGameObject) override;

private:
	Model OtherPlayerModel;
};

