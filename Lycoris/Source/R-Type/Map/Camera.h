#pragma once

class Camera
{
public:

	void MoveCamera(const float deltaTime);
	void ResetPosition();

	float GetPosX() const;
	float GetPosY() const;

private:
	float m_PosX = 0.f;
	float m_PosY = 0.f;
	float m_Speed = 100.f;
};
