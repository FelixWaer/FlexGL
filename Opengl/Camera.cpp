#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

glm::mat4 Camera::get_CameraView()
{
	return glm::lookAt(CameraPos, CameraPos+CameraTarget, CameraUp);
}

glm::mat4 Camera::get_CameraProjection()
{
	return glm::mat4(1.f);
}

void Camera::update_CameraPosition(glm::vec3 positionVector)
{
	CameraPos = positionVector;
}

void Camera::move_CameraFront(bool moveFront)
{
	if (moveFront == true)
	{
		CameraPos += CameraSpeed * CameraTarget;
	}
	else
	{
		CameraPos -= CameraSpeed * CameraTarget;
	}
}

void Camera::move_CameraSide(bool moveRight)
{
	if (moveRight == true)
	{
		CameraPos += glm::normalize(glm::cross(CameraTarget, CameraUp)) * CameraSpeed;
	}
	else
	{
		CameraPos -= glm::normalize(glm::cross(CameraTarget, CameraUp)) * CameraSpeed;
	}
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
