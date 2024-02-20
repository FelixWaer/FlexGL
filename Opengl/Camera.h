#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;

	glm::mat4 get_CameraView();
	glm::mat4 get_CameraProjection();
	void update_CameraPosition(glm::vec3 positionVector);
	void move_CameraFront(bool moveFront);
	void move_CameraSide(bool moveRight);
	void update_CameraRotation(float xRotation, float yRotation);
	void set_CameraSpeed(float newSpeed);
private:
	glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 CameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float CameraSpeed = 0.5f;
	float Yaw = -90.f;
	float Pitch = 0.f;
};

