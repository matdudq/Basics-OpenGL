#pragma once
#include "Camera.h"
#include "GLFW/glfw3.h"

class CameraController
{
private:
	Camera& m_Camera;
	GLFWwindow& m_Window;

	glm::vec2 m_CursorPos;

	float moveSpeed = 5.0f;
	float cameraRotationSpeed = 5.0f;

public:
	CameraController(Camera& camera, GLFWwindow& window);
	~CameraController();

	void Update(double deltaTime);
	glm::vec3 GetCameraPosition();
};

