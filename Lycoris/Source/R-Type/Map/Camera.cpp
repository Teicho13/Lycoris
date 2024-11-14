#include "R-Type/Map/Camera.h"

void Camera::MoveCamera(const float deltaTime)
{
	m_PosX += m_Speed * deltaTime;
}

void Camera::ResetPosition()
{
	m_PosX = 0.f;
	m_PosY = 0.f;
}

float Camera::GetPosX() const
{
	return m_PosX;
}

float Camera::GetPosY() const
{
	return m_PosY;
}
