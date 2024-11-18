#include <SDL_rect.h>
#include <SDL_timer.h>
#include <iostream>

#include "Entities/Entity.h"
#include "Core/Sprite.h"
#include "Managers/TextureManager.h"


Entity::Entity(const char* texturePath)
{
	m_Sprite.reset(new Sprite(texturePath));
	m_Size.x = m_Sprite->GetWidth();
	m_Size.y = m_Sprite->GetHeight();
	m_Position.x = 0.f;
	m_Position.y = 0.f;
	m_Animation.Initialize(m_Sprite->GetFrames());
	m_Animation.SetFrameSpeed(8);
}

Entity::Entity(const char* texturePath, const int columns, const int rows)
{
	m_Sprite.reset(new Sprite(texturePath,columns,rows));
	m_Size.x = m_Sprite->GetWidth();
	m_Size.y = m_Sprite->GetHeight();
	m_Position.x = 0.f;
	m_Position.y = 0.f;
	m_Animation.Initialize(m_Sprite->GetFrames());
	m_Animation.SetFrameSpeed(8);
}

Entity::Entity(const char* texturePath, const int columns, const int rows, float posX, float posY)
{
	m_Sprite.reset(new Sprite(texturePath, columns, rows));
	m_Size.x = m_Sprite->GetWidth();
	m_Size.y = m_Sprite->GetHeight();
	m_Position.x = posX;
	m_Position.y = posY;
	m_Animation.Initialize(m_Sprite->GetFrames());
	m_Animation.SetFrameSpeed(8);
}

void Entity::Draw() const
{
	if(m_Sprite != nullptr)
	{
		//Create Variable for the position of the sprite
		const SDL_FRect tempRec(m_Position.x, m_Position.y, static_cast<float>(m_Sprite->GetWidth()), static_cast<float>(m_Sprite->GetHeight()));

		//Create temp variable to get the position / size that needs to be rendered
		SDL_Rect tempSource;
		m_Sprite->GetSourceRec(tempSource);

		TextureManager::RenderTexture(m_Sprite->GetTexture(), &tempSource, &tempRec);
	}
}

void Entity::SetPosX(float posX)
{
	m_Position.x = posX;
}

void Entity::SetPosY(float posY)
{
	m_Position.y = posY;
}

void Entity::SetSize(SDL_Point newSize)
{
	m_Size = newSize;
}

void Entity::SetSize(int w, int h)
{
	m_Size.x = w;
	m_Size.y = h;
}

void Entity::SetWidth(int width)
{
	m_Size.x = width;
}

void Entity::SetHeight(int height)
{
	m_Size.y = height;
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

bool Entity::IsOutBounds() const
{
	if(GetPosition().x + static_cast<float>(GetSize().x) + 1.f <= 0.f)
	{
		return true;
	}
	return false;
}

void Entity::SetPosition(SDL_FPoint newPos)
{
	m_Position = newPos;
}

void Entity::SetPosition(float posX, float posY)
{
	m_Position.x = posX;
	m_Position.y = posY;
}

SDL_FPoint Entity::GetPosition() const
{
	return m_Position;
}

SDL_Point Entity::GetSize() const
{
	return m_Size;
}

void Entity::Animate(float dt)
{
	m_Animation.Update(dt);
	GetSprite()->SetFrame(m_Animation.GetCurrentFrame());
}

void Entity::SetFrameSpeed(float delay)
{
	if (delay <= 0)
		delay = 1;

	m_Animation.SetFrameSpeed(delay);
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
