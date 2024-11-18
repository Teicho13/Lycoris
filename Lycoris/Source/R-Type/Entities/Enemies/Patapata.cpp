#include "R-Type/Entities/Enemies/Patapata.h"

#include <iostream>
#include <SDL_timer.h>
#include "Core/Sprite.h"

Patapata::Patapata(const char* texturePath, const int columns, const int rows)
	: Entity(texturePath, columns, rows)
{
	GetAnimationComponent().Play();
}

Patapata::Patapata(const char* texturePath, const int columns, const int rows, float posX, float posY)
	: Entity(texturePath, columns, rows,posX,posY)
{
	GetAnimationComponent().Play();
	m_StartX = posX;
	m_StartY = posY;
}

void Patapata::Update(float deltaTime)
{
	Move(deltaTime);
	Animate(deltaTime);
	if(IsOutBounds())
	{
		Die();
	}
}

void Patapata::Move(float dt)
{
	//Move based on sine wave offset by the Y start position
	float sine = (m_WaveFrequency * sinf(static_cast<float>(static_cast<double>(SDL_GetTicks()) * 0.5 * M_PI / m_WaveSpeed)) + m_StartY);
	SetPosY(sine);

	SetPosX(GetPosition().x - (m_MoveSpeed * dt));

}
