#include "./R-Type/Entities/Player.h"

#include <iostream>
#include <SDL_timer.h>

#include "./Core/Sprite.h"

#include "./Core/Utility/KeyStates.h"
#include "./Core/Utility/AppConfig.h"
#include "R-Type/Map/Camera.h"
#include "R-Type/Map/Map.h"
#include "R-Type/Map/Tile.h"

#include "./Extras/VisualEffect.h"


Player::Player(const char* texturePath)
	: Entity(texturePath)
{
	SetWidth(GetWidth() - 10);
	SetHeight(GetHeight() - 10);

	m_ChargeVFX = std::make_unique<VisualEffect>("Assets/Games/R-Type/Textures/Player/Charging.png", 8, 1, 50.f, 50.f, true);
	m_DieVFX = std::make_unique<VisualEffect>("Assets/Games/R-Type/Textures/Player/PlayerExplosion.png", 8, 1, 50.f, 50.f, false,false,this);
	m_DieVFX->SetPlayer(this);
}

Player::Player(const char* texturePath, const int columns, const int rows)
	: Entity(texturePath,columns,rows)
{
	SetWidth(GetWidth() - 10);
	SetHeight(GetHeight() - 10);

	m_ChargeVFX = std::make_unique<VisualEffect>("Assets/Games/R-Type/Textures/Player/Charging.png", 8, 1, 50.f, 50.f, true);
	m_DieVFX = std::make_unique<VisualEffect>("Assets/Games/R-Type/Textures/Player/PlayerExplosion.png", 8, 1, 50.f, 50.f, false,false,this);
	m_DieVFX->SetPlayer(this);
}

void Player::Draw() const
{
	if(!IsExploding())
	{
		Entity::Draw();
	}
	else
	{
		m_DieVFX->Draw();
		return;
	}
	if(m_InputHeld && m_Charge > 10.f)
	{
		m_ChargeVFX->Draw();
	}
	
}

void Player::Update(float deltaTime)
{
	if(!IsExploding())
	{
		HandleMovement(deltaTime);
		HandleBoundChecks();
		ChargeBullet(deltaTime);
		if(m_InputHeld)
		{
			m_ChargeVFX->Update();
		}
	}
	else
	{
		m_DieVFX->SetPosX(GetPosX());
		m_DieVFX->SetPosY(GetPosY());
		m_DieVFX->Update();
	}
	
}

bool Player::HandleTileCollision(Map* map) const
{
	if(m_CamerRef == nullptr)
		return false;


	int posX = (static_cast<int>(GetPosX() + m_CamerRef->GetPosX())) / 64;
	int posX2 = (static_cast<int>(GetPosX() + m_CamerRef->GetPosX()) + GetWidth()) / 64;

	int posY = static_cast<int>(GetPosY() / 64);
	int posY2 = (static_cast<int>(GetPosY()) + GetHeight()) / 64;

	if (posY2 > (Map::m_MapRows - 1))
		posY2 = 11;

	if(map->HasTileCollision(posX, posX2, posY, posY2))
	{
		return true;
	}

	return false;
}

void Player::SetCamera(Camera* camera)
{
	m_CamerRef = camera;
}

Camera* Player::GetCamera(Camera* camera) const
{
	return m_CamerRef;
}

void Player::HandleMovement(float dt)
{
	if(g_KeyStates[SDL_SCANCODE_A])
	{
		SetPosX(GetPosX() + -m_MoveSpeed * dt);
	}

	if(g_KeyStates[SDL_SCANCODE_D])
	{
		SetPosX(GetPosX() + m_MoveSpeed * dt);
	}

	if(g_KeyStates[SDL_SCANCODE_W])
	{
		SetPosY(GetPosY() + -m_MoveSpeed * dt);
	}

	if(g_KeyStates[SDL_SCANCODE_S])
	{
		SetPosY(GetPosY() + m_MoveSpeed * dt);
	}

	m_ChargeVFX->SetPosX(GetPosX() + static_cast<float>(GetWidth()) + m_ChargePosXOffset);
	m_ChargeVFX->SetPosY((GetPosY() + static_cast<float>(GetHeight()) / 2) + m_ChargePosYOffset);
}

void Player::HandleBoundChecks()
{
	if(GetPosY() <= 0)
	{
		SetPosY(0);
	}

	if(GetPosX() <= 0)
	{
		SetPosX(0);
	}

	if(static_cast<int>(GetPosY()) + GetHeight() >= AppConfig::Height)
	{
		SetPosY(static_cast<float>(AppConfig::Height - GetHeight()));
	}

	if(static_cast<int>(GetPosX()) + GetWidth() >= AppConfig::Width)
	{
		SetPosX(static_cast<float>(AppConfig::Width - GetWidth()));
	}
}

void Player::SetMovementSpeed(float amount)
{
	m_MoveSpeed = amount;
}

float Player::GetMovementSpeed() const
{
	return m_MoveSpeed;
}

void Player::Die()
{
	m_IsAlive = false;
}

void Player::Explode()
{
	m_IsExploding = true;
	m_DieVFX->GetAnimation()->ResetAnimation();
	m_DieVFX->GetAnimation()->Play();
}

bool Player::IsExploding() const
{
	return m_IsExploding;
}

bool Player::IsAlive() const
{
	return m_IsAlive;
}

void Player::ChargeBullet(float dt)
{
	if(m_InputHeld)
	{
		if(!m_Charged)
		{
			m_Charge += (m_ChargeSpeed * dt);
			if(m_Charge >= 100.f)
			{
				m_Charged = true;
				m_Charge = 100.f;
				std::cout << "Fully Charged !" << "\n";
			}
		}
	}
	else
	{
		if(m_Charged || m_Charge > 0.f)
		{
			m_Charge = 0.f;
			m_Charged = false;
			std::cout << "Charge Reset !" << "\n";
		}
		m_ChargeVFX->GetAnimation()->ResetAnimation();
	}
}

bool Player::FullyCharged() const
{
	return m_Charged;
}
