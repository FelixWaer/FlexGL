#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

glm::mat4 Camera::get_CameraView()
{
	return glm::lookAt(CameraPos, CameraFront, CameraUp);
}

glm::mat4 Camera::get_CameraProjection()
{
	return glm::mat4(1.f);
}

void Camera::update_CameraPosition(glm::vec3 updateVector)
{
	CameraPos += updateVector;
	CameraFront += updateVector;
}

void Camera::set_CameraSpeed(float newSpeed)
{
	CameraSpeed = newSpeed;
}
