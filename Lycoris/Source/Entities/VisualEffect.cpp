#include "./Extras/VisualEffect.h"

#include <iostream>
#include "managers/TextureManager.h"
#include <SDL_rect.h>

#include "./Core/Sprite.h"
#include "./R-Type/Entities/Player.h"


VisualEffect::VisualEffect(const char* texturePath, const int columns, const int rows, float posX, float posY,
                           bool looping, bool startOn, Player* player)
{
	m_Sprite.reset(new Sprite(texturePath, columns, rows));
	m_Width = m_Sprite->GetWidth();
	m_Height = m_Sprite->GetHeight();
	m_PosX = posX;
	m_PosY = posY;
	m_Animation.Initialize(m_Sprite->GetFrames(),this);
	m_Animation.SetFrameDelay(100);
	m_Animation.SetLooped(looping);
	m_Animation.ResetAnimation();
	if(startOn)
	{
		m_Animation.Play();
	}
	m_Player = player;
}


//Function that triggers after animation is done playing
void VisualEffect::Callback()
{
	std::cout << "CALLBACK !\n";
	if(m_Player != nullptr)
	{
		if(m_Player->IsExploding())
		{
			m_Player->Die();
		}
	}
}

void VisualEffect::Draw()
{
	if (m_Sprite != nullptr)
	{
		//Create Variable for the position of the sprite
		const SDL_FRect tempRec(m_PosX, m_PosY, static_cast<float>(m_Sprite->GetWidth()), static_cast<float>(m_Sprite->GetHeight()));

		//Create temp variable to get the position / size that needs to be rendered
		SDL_Rect tempSource;
		m_Sprite->GetSourceRec(tempSource);

		TextureManager::RenderTexture(m_Sprite->GetTexture(), &tempSource, &tempRec);
	}
}

void VisualEffect::Update()
{
	m_Animation.Update();
	GetSprite()->SetFrame(m_Animation.GetCurrentFrame());
}

void VisualEffect::SetPosX(float newX)
{
	m_PosX = newX;
}

void VisualEffect::SetPosY(float newY)
{
	m_PosY = newY;
}

Sprite* VisualEffect::GetSprite() const
{
	return m_Sprite.get();
}

Animation* VisualEffect::GetAnimation()
{
	return &m_Animation;
}

void VisualEffect::SetPlayer(Player* player)
{
	player = m_Player;
}
