#include <SDL_rect.h>
#include <SDL_timer.h>
#include <iostream>

#include "Entities/Entity.h"
#include "Core/Sprite.h"
#include "Managers/TextureManager.h"


Entity::Entity(const char* texturePath)
{
	m_Sprite.reset(new Sprite(texturePath));
	m_Width = m_Sprite->GetWidth();
	m_Height = m_Sprite->GetHeight();
	m_PosX = 0.f;
	m_PosY = 0.f;
	m_Animation.Initialize(m_Sprite->GetFrames());
	m_Animation.SetFrameDelay(100);
}

Entity::Entity(const char* texturePath, const int columns, const int rows)
{
	m_Sprite.reset(new Sprite(texturePath,columns,rows));
	m_Width = m_Sprite->GetWidth();
	m_Height = m_Sprite->GetHeight();
	m_PosX = 0.f;
	m_PosY = 0.f;
	m_Animation.Initialize(m_Sprite->GetFrames());
	m_Animation.SetFrameDelay(100);
}

Entity::Entity(const char* texturePath, const int columns, const int rows, float posX, float posY)
{
	m_Sprite.reset(new Sprite(texturePath, columns, rows));
	m_Width = m_Sprite->GetWidth();
	m_Height = m_Sprite->GetHeight();
	m_PosX = posX;
	m_PosY = posY;
	m_Animation.Initialize(m_Sprite->GetFrames());
	m_Animation.SetFrameDelay(100);
}

void Entity::Draw() const
{
	if(m_Sprite != nullptr)
	{
		//Create Variable for the position of the sprite
		const SDL_FRect tempRec(m_PosX, m_PosY, static_cast<float>(m_Sprite->GetWidth()), static_cast<float>(m_Sprite->GetHeight()));

		//Create temp variable to get the position / size that needs to be rendered
		SDL_Rect tempSource;
		m_Sprite->GetSourceRec(tempSource);

		TextureManager::RenderTexture(m_Sprite->GetTexture(), &tempSource, &tempRec);
	}
}

void Entity::SetPosX(float pos)
{
	m_PosX = pos;
}

void Entity::SetPosY(float pos)
{
	m_PosY = pos;
}

void Entity::SetWidth(int width)
{
	m_Width = width;
}

void Entity::SetHeight(int height)
{
	m_Height = height;
}

void Entity::SetCanDie()
{
	m_ShouldDie = true;

	//Do Animation here first

	Die();
}

void Entity::Die()
{
	m_CanRemove = true;
}

bool Entity::ShouldRemove() const
{
	return m_CanRemove;
}

bool Entity::IsOutBounds()
{
	if(GetPosX() + static_cast<float>(GetWidth()) + 1.f <= 0.f)
	{
		return true;
	}
	return false;
}

float Entity::GetPosX() const
{
	return m_PosX;
}

float Entity::GetPosY() const
{
	return m_PosY;
}

void Entity::GetPosXY(float& posX, float& posY) const
{
	posX = m_PosX;
	posY = m_PosY;
}

int Entity::GetWidth() const
{
	return m_Width;
}

int Entity::GetHeight() const
{
	return m_Height;
}

void Entity::Animate()
{
	m_Animation.Update();
	GetSprite()->SetFrame(m_Animation.GetCurrentFrame());
}

//Sets delay between frames in ms
void Entity::SetFrameDelay(int delay)
{
	if (delay <= 0)
		delay = 100;

	m_Animation.SetFrameDelay(delay);
}

Animation& Entity::GetAnimationComponent()
{
	return m_Animation;
}

bool Entity::GetIsAnimated() const
{
	return m_IsAnimated;
}

//Returns delay between each frame in ms
int Entity::GetFrameDelay() const
{
	return m_FrameDelay;
}

Sprite* Entity::GetSprite() const
{
	return m_Sprite.get();
}
