#include "SceneCamera.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/CameraComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/SphereCollComponent.h"
#include "../Components/TagComponent.h"
#include "../Engine/Input.h"

void SceneCamera::tick(float deltaTime)
{
	glm::vec2 newMousePos = EngineManager::get()->get_MousePosition();

	float xOffset = (newMousePos.x - mousePos.x) * 0.1f;
	float yOffset = (mousePos.y - newMousePos.y) * 0.1f;
	mousePos = newMousePos;
	
	Yaw += xOffset;
	Pitch += yOffset;
	if (Pitch > 89.f)
	{
		Pitch = 89.f;
	}
	else if (Pitch < -89.f)
	{
		Pitch = -89.f;
	}

	glm::vec3 tempRotationVector;
	
	tempRotationVector.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	tempRotationVector.y = sin(glm::radians(Pitch));
	tempRotationVector.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	get_Component<CameraComponent>().CameraDirection = glm::normalize(tempRotationVector);
}

void SceneCamera::init_Entity()
{
	std::cout << "EntityID: " << this->get_EntityID() << std::endl;
	add_Component<PositionComponent>();
	add_Component<MovementComponent>();
	add_Component<TransformComponent>();
	add_Component<CameraComponent>();
	add_Component<SphereCollComponent>();
	add_Component<TagComponent>();
	//add_Component<PhysicsComponent>();

	W_InputEvent = make_Event(this, &SceneCamera::input_WFunction);
	A_InputEvent = make_Event(this, &SceneCamera::input_AFunction);
	S_InputEvent = make_Event(this, &SceneCamera::input_SFunction);
	D_InputEvent = make_Event(this, &SceneCamera::input_DFunction);
	Space_InputEvent = make_Event(this, &SceneCamera::input_SpaceFunction);
	CTRL_InputEvent = make_Event(this, &SceneCamera::input_CTRLFunction);
	ESC_InputEvent = make_Event(this, &SceneCamera::input_ESCFunction);

	Input::bind_EventToKey(W_InputEvent, Key::W, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(A_InputEvent, Key::A, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(S_InputEvent, Key::S, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(D_InputEvent, Key::D, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(Space_InputEvent, Key::Space, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(CTRL_InputEvent, Key::CTRL, KeyPress::WhileHeldDown);
	Input::bind_EventToKey(ESC_InputEvent, Key::ESCAPE, KeyPress::OnPress);

	get_Component<MovementComponent>().Speed = 10.f;
	get_Component<CameraComponent>().CameraDirection = glm::vec3(0.f, 0.f, 1.f);
	get_Component<SphereCollComponent>().Radius = 2.f;
	get_Component<TagComponent>().Tag = "Player";

	mousePos = EngineManager::get()->get_MousePosition();
	EngineManager::get()->set_MousePosCenter();

	enable_Ticking();
	EngineManager::get()->get_ActiveScene()->set_ActiveCamera(this);
}

void SceneCamera::input_WFunction()
{
	get_Component<MovementComponent>().Acceleration += get_Component<CameraComponent>().CameraDirection * CameraSpeed;
}

void SceneCamera::input_AFunction()
{
	glm::vec3 newDirection = glm::normalize(glm::cross(get_Component<CameraComponent>().CameraDirection, get_Component<CameraComponent>().CameraUp));
	get_Component<MovementComponent>().Acceleration += -newDirection * CameraSpeed;
}

void SceneCamera::input_SFunction()
{
	get_Component<MovementComponent>().Acceleration += -get_Component<CameraComponent>().CameraDirection * CameraSpeed;
}

void SceneCamera::input_DFunction()
{
	glm::vec3 newDirection = glm::normalize(glm::cross(get_Component<CameraComponent>().CameraDirection, get_Component<CameraComponent>().CameraUp));
	get_Component<MovementComponent>().Acceleration += newDirection * CameraSpeed;
}

void SceneCamera::input_SpaceFunction()
{
	get_Component<MovementComponent>().Acceleration.y += 1.f * CameraSpeed;
}

void SceneCamera::input_CTRLFunction()
{
	get_Component<MovementComponent>().Acceleration.y += -1.f * CameraSpeed;
}

void SceneCamera::input_ESCFunction()
{
	EngineManager::get()->get_ActiveWindow().close_Window();
}
