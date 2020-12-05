#include "CameraController.h"
#include <iostream>
CameraController::CameraController(Camera& camera, GLFWwindow& window) : m_Camera(camera), m_Window(window)
{
}

CameraController::~CameraController()
{
}

void CameraController::Update(double deltaTime)
{
	double cursorPositionX, cursorPositionY;
	glfwGetCursorPos(&m_Window, &cursorPositionX, &cursorPositionY);

	glm::vec3 moveVector = glm::vec3(0.0f,0.0f,0.0f);

	if (glfwGetKey(&m_Window, GLFW_KEY_LEFT) == GLFW_PRESS) 
		moveVector += glm::normalize(glm::cross(m_Camera.GetUpVector(), m_Camera.GetFrontVector())) * (float)deltaTime * moveSpeed;
	if (glfwGetKey(&m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS) 
		moveVector -= glm::normalize(glm::cross(m_Camera.GetUpVector(), m_Camera.GetFrontVector())) * (float)deltaTime * moveSpeed;

	if (glfwGetKey(&m_Window, GLFW_KEY_UP) == GLFW_PRESS) 
		moveVector += moveSpeed * (float)deltaTime * m_Camera.GetFrontVector();
	if (glfwGetKey(&m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
		moveVector -= moveSpeed * (float)deltaTime * m_Camera.GetFrontVector();

	m_Camera.MoveCamera(moveVector);

	if (glfwGetMouseButton(&m_Window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		glm::vec2 mouseVector(cursorPositionX - m_CursorPos.x, cursorPositionY - m_CursorPos.y);
		glm::normalize(mouseVector);

		m_Camera.RotateCamera(mouseVector.x * moveSpeed * deltaTime, mouseVector.y * moveSpeed * deltaTime);
	}

	m_CursorPos = glm::vec2(cursorPositionX, cursorPositionY);
}

glm::vec3 CameraController::GetCameraPosition()
{
	return m_Camera.GetPosition();
}
