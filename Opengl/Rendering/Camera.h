#pragma once
#include <glm/glm.hpp>

class GameObject;

class Camera
{
public:
	Camera() = default;

	glm::mat4 get_CameraView();
	glm::mat4 get_CameraProjection();
	glm::vec3& get_CameraPosition();
	glm::vec3 get_CameraRotation();
	glm::vec3 get_CameraTarget();
	void update_CameraPosition(glm::vec3 positionVector);
	void move_CameraFront(bool moveFront);
	void move_CameraSide(bool moveRight);
	void move_CameraUp(float yPos);
	void update_CameraRotation(float xRotation, float yRotation);
	void set_CameraSpeed(float newSpeed);
	void attach_ToGameObject(GameObject* GO);
	void set_CameraHeight(float yPos);
	void lock_CameraPitch(float degrees);
	void turn_CameraAround();

private:
	glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 CameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float CameraSpeed = 0.5f;
	float Yaw = -90.f;
	float Pitch = 0.f;

	GameObject* AttachedGameObject;
};

