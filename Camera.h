#pragma once
#include "glm/glm.hpp"
#include "glad/glad.h"

enum class CameraProjectionType
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera
{
private:
	CameraProjectionType m_Type;

	glm::mat4 m_Proj;
	glm::mat4 m_View;

	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraFront;

	float m_Yaw;
	float m_Pitch;

	float m_AspectRatio;
public:
	Camera(const glm::vec3& startingPosition, const glm::vec3& lookAtPosition);
	~Camera();

	void SetCameraPerspective(float fov, float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.0f);
	void SetCameraOrthographic(float cameraSize, float aspectRatio, float nearPlane, float farPlane);

	void SetCameraSize(float size);
	void MoveCamera(const glm::vec3& direction);
	void RotateCamera(const glm::vec2& rotationAngles);
	void RotateCamera(const float yaw, const float pitch);

	inline glm::mat4 GetVPMatirx() const
	{
		return  m_Proj * m_View;
	}

	inline CameraProjectionType GetProjectionType() const
	{
		return m_Type;
	}

	inline glm::vec3 GetPosition() const
	{
		return m_CameraPos;
	}

	inline glm::vec3 GetUpVector() const
	{
		return m_CameraUp;
	}

	inline glm::vec3 GetFrontVector() const
	{
		return m_CameraFront;
	}

private:
	void UpdateCameraRotation();
	void UpdateCameraViewMatrix();
};