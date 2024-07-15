#pragma once
#include "../Engine/GameObject.h"
#include "../Rendering/Camera.h"

class EngineCamera : public GameObject
{
public:
	void game_Start() override;
	void tick(float deltaTime) override;

private:

	Camera ActiveCamera;
};

