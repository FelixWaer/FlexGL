#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../Engine/EngineManager.h"
#include "../Engine/GameObject.h"

void Camera::init_Camera()
{
	EngineManager::TheEngineManager->add_ToCameraHandler(this);
}

glm::mat4 Camera::get_CameraView()
{
	return glm::lookAt(CameraPos, CameraPos+CameraTarget, CameraUp);
}

glm::mat4 Camera::get_CameraProjection()
{
	return glm::mat4(1.f);
}

glm::vec3& Camera::get_CameraPosition()
{
	return CameraPos;
}

glm::vec3 Camera::get_CameraRotation()
{
	return glm::vec3(Yaw, Pitch, 0.f);
}

glm::vec3 Camera::get_CameraTarget()
{
	return CameraTarget;
}

void Camera::update_CameraPosition(glm::vec3 positionVector)
{
	CameraPos = positionVector;
}

void Camera::move_CameraFront(bool moveFront)
{
	if (moveFront == true)
	{
		CameraPos += CameraTarget * CameraSpeed * EngineManager::TheEngineManager->get_DeltaTime();
	}
	else
	{
		CameraPos -= CameraTarget * CameraSpeed * EngineManager::TheEngineManager->get_DeltaTime();
	}
}

void Camera::move_CameraSide(bool moveRight)
{
	if (moveRight == true)
	{
		CameraPos += glm::normalize(glm::cross(CameraTarget, CameraUp)) * CameraSpeed * EngineManager::TheEngineManager->get_DeltaTime();
	}
	else
	{
		CameraPos -= glm::normalize(glm::cross(CameraTarget, CameraUp)) * CameraSpeed * EngineManager::TheEngineManager->get_DeltaTime();
	}
}

void Camera::move_CameraUp(float yPos)
{
	CameraPos.y += yPos;
}

void Camera::update_CameraRotation(float xRotation, float yRotation)
{
	glm::vec3 tempRotationVector;

	Yaw += xRotation;
	Pitch += yRotation;
	if (Pitch > 89.f)
	{
		Pitch = 89.f;
	}
	else if (Pitch < -89.f)
	{
		Pitch = -89.f;
	}

	tempRotationVector.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	tempRotationVector.y = sin(glm::radians(Pitch));
	tempRotationVector.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	CameraTarget = glm::normalize(tempRotationVector);
}

void Camera::set_CameraSpeed(float newSpeed)
{
	CameraSpeed = newSpeed;
}

void Camera::attach_ToGameObject(GameObject* GO)
{
	AttachedGameObject = GO;
}

void Camera::set_CameraHeight(float yPos)
{
	CameraPos.y = yPos;
}

void Camera::lock_CameraPitch(float degrees)
{
	Pitch = degrees;
}

void Camera::turn_CameraAround()
{
	Yaw *= -1;
}
