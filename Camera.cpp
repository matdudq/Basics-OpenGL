#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(const glm::vec3& cameraPosition, const glm::vec3& lookAtPosition) 
{
	m_Type = CameraProjectionType::PERSPECTIVE;

	m_CameraPos = cameraPosition; 
	m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_Yaw = 270;
	m_Pitch = 0;

	UpdateCameraRotation();
}

Camera::~Camera()
{

}

void Camera::SetCameraPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_Type = CameraProjectionType::PERSPECTIVE;
	m_Proj = glm::perspective(fov, (GLfloat)aspectRatio, nearPlane, farPlane);
}

void Camera::SetCameraOrthographic(float cameraSize, float aspectRatio, float nearPlane, float farPlane)
{
	m_Type = CameraProjectionType::ORTHOGRAPHIC;
	m_Proj = glm::ortho(-cameraSize * aspectRatio, cameraSize * aspectRatio, -cameraSize, cameraSize, 0.1f, 100.0f);
}

void Camera::MoveCamera(const glm::vec3& displacement)
{
	m_CameraPos += displacement;
	UpdateCameraViewMatrix();
}

void Camera::RotateCamera(const glm::vec2& rotationAngles)
{
	m_Yaw += rotationAngles.y;
	m_Pitch += rotationAngles.x;
	UpdateCameraRotation();
}
void Camera::RotateCamera(const float yaw, const float pitch)
{
	m_Yaw += yaw;
	m_Pitch += pitch;
	UpdateCameraRotation();
}

void Camera::UpdateCameraRotation()
{
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	m_CameraFront.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraFront.y = sin(glm::radians(m_Pitch));
	m_CameraFront.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_CameraFront = glm::normalize(m_CameraFront);
	UpdateCameraViewMatrix();
}

void Camera::UpdateCameraViewMatrix()
{
	m_View = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}
