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
	SetWidth(GetSize().x - 10);
	SetHeight(GetSize().y - 10);

	m_ChargeVFX = std::make_unique<VisualEffect>("Assets/Games/R-Type/Textures/Player/Charging.png", 8, 1, 50.f, 50.f, true);
	m_DieVFX.reset(new VisualEffect("Assets/Games/R-Type/Textures/Player/PlayerExplosion.png", 8, 1, 50.f, 50.f, false,false,this));
	m_DieVFX->SetEntity(this);
}

Player::Player(const char* texturePath, const int columns, const int rows)
	: Entity(texturePath,columns,rows)
{
	SetWidth(GetSize().x - 10);
	SetHeight(GetSize().y - 10);

	m_ChargeVFX = std::make_unique<VisualEffect>("Assets/Games/R-Type/Textures/Player/Charging.png", 8, 1, 50.f, 50.f, true);
	m_DieVFX.reset(new VisualEffect("Assets/Games/R-Type/Textures/Player/PlayerExplosion.png", 8, 1, 50.f, 50.f, false,false,this));
	m_DieVFX->SetEntity(this);
}

Player::~Player()
{
	m_ChargeVFX.reset(nullptr);
	m_DieVFX.reset(nullptr);
	m_Charge = 0.f;
	m_Charged = false;
	m_CamerRef = nullptr;
}

void Player::Draw() const
{
	Entity::Draw();
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
			m_ChargeVFX->Update(deltaTime);
		}

		SteerShip(deltaTime);
	}
	else
	{
		m_DieVFX->SetPosX(GetPosition().x);
		m_DieVFX->SetPosY(GetPosition().y);
		m_DieVFX->Update(deltaTime);
	}
	
}

bool Player::HandleTileCollision(Map& map) const
{
	if(m_CamerRef == nullptr)
		return false;


	//Check overlapping tiles
	
	const int posX = (static_cast<int>(GetPosition().x + m_CamerRef->GetPosX())) / AppConfig::TileSize;
	const int posX2 = (static_cast<int>(GetPosition().x + m_CamerRef->GetPosX()) + GetSize().x) / AppConfig::TileSize;

	const int posY = static_cast<int>(GetPosition().y / AppConfig::TileSize);
	int posY2 = (static_cast<int>(GetPosition().y) + GetSize().y) / AppConfig::TileSize;

	if (posY2 > (Map::m_MapRows - 1))
		posY2 = 11;

	//Check if tiles can be collided with
	if(map.HasTileCollision(posX, posX2, posY, posY2))
	{
		return true;
	}

	return false;
}

//Change player animation based on the direction the player is moving.
void Player::SteerShip(float dt)
{
	//Increment over time
	SteerCurrentVal += (6 * dt);

	if(SteerCurrentVal >= SteerThreshold)
	{
		//Reset Value for next animation frame
		SteerCurrentVal = 0;

		//Check if we are either moving up/down or neither (reset position to center)
		switch (SteerDirection)
		{
		case 1 :
			if(GetSprite()->GetCurrentFrame() < GetSprite()->GetFrames())
			{
				GetSprite()->SetFrame(GetSprite()->GetCurrentFrame() + 1);
			}
			break;
			
		case -1:
			if(GetSprite()->GetCurrentFrame() > 0)
			{
				GetSprite()->SetFrame(GetSprite()->GetCurrentFrame() - 1);
			}
			break;

		default:
			if(GetSprite()->GetCurrentFrame() > 2)
			{
				GetSprite()->SetFrame(GetSprite()->GetCurrentFrame() - 1);
			}
			if(GetSprite()->GetCurrentFrame() < 2)
			{
				GetSprite()->SetFrame(GetSprite()->GetCurrentFrame() + 1);
			}
			break;
		}
	}
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
	SteerDirection = 0;
	
	if(g_KeyStates[SDL_SCANCODE_A])
	{
		SetPosX(GetPosition().x + -m_MoveSpeed * dt);
	}

	if(g_KeyStates[SDL_SCANCODE_D])
	{
		SetPosX(GetPosition().x + m_MoveSpeed * dt);
	}

	if(g_KeyStates[SDL_SCANCODE_W])
	{
		SetPosY(GetPosition().y + -m_MoveSpeed * dt);
		SteerDirection = 1;
	}

	if(g_KeyStates[SDL_SCANCODE_S])
	{
		SetPosY(GetPosition().y + m_MoveSpeed * dt);
		SteerDirection = -1;
	}

	m_ChargeVFX->SetPosX(GetPosition().x + static_cast<float>(GetSize().x) + m_ChargePosXOffset);
	m_ChargeVFX->SetPosY((GetPosition().y + static_cast<float>(GetSize().y) / 2) + m_ChargePosYOffset);
}

void Player::HandleBoundChecks()
{
	if(GetPosition().y <= 0)
	{
		SetPosY(0);
	}

	if(GetPosition().x <= 0)
	{
		SetPosX(0);
	}

	if(static_cast<int>(GetPosition().y) + GetSize().y >= AppConfig::Height)
	{
		SetPosY(static_cast<float>(AppConfig::Height - GetSize().y));
	}

	if(static_cast<int>(GetPosition().x) + GetSize().x >= AppConfig::Width)
	{
		SetPosX(static_cast<float>(AppConfig::Width - GetSize().x));
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
