#pragma once
#include "Entities/Entity.h"

class Patapata : public Entity
{
public:
	Patapata(const char* texturePath, const int columns, const int rows);
	Patapata(const char* texturePath, const int columns, const int rows, float posX, float posY);

	void Update(float deltaTime) override;
	void Move(float dt);

private:
	float m_StartX = 0.f;
	float m_StartY = 0.f;
	float m_MoveSpeed = 200.f;

	//How fast the wave goes. (higher goes slower)
	float m_WaveSpeed = 500.f;
	//Determines the height of the wave.
	float m_WaveFrequency = 100.f;
};
