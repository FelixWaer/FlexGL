#pragma once
#include "Entity.h"

#include "../Engine/EventCallback.h"

class SceneCamera : public Entity
{
public:
	void tick(float deltaTime) override;

protected:
	void init_Entity() override;

private:
	Event* W_InputEvent = nullptr;
	Event* A_InputEvent = nullptr;
	Event* S_InputEvent = nullptr;
	Event* D_InputEvent = nullptr;
	Event* Space_InputEvent = nullptr;
	Event* CTRL_InputEvent = nullptr;
	Event* ESC_InputEvent = nullptr;
	Event* One_InputEvent = nullptr;

	glm::vec2 mousePos = glm::vec2(0.f);
	float CameraSpeed = 20.f;
	float Pitch = 0.f;
	float Yaw = 89.f;
	bool FreeFlying = true;

	void input_WFunction();
	void input_AFunction();
	void input_SFunction();
	void input_DFunction();
	void input_SpaceFunction();
	void input_CTRLFunction();
	void input_ESCFunction();
	void input_OneFunction();
};

