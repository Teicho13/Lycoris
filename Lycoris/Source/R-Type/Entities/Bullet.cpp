#include "./R-Type/Entities/Bullet.h"
#include "./Core/Utility/AppConfig.h"

Bullet::Bullet(const char* texturePath, bool charged)
	: Projectile(texturePath)
{
	m_IsCharged = charged;
	m_Damage = charged ? 3 : 1;
	m_Pierce = charged ? true : false;
	if(charged)
	{
		m_DieVFX.reset(new VisualEffect("Assets/Games/R-Type/Textures/Player/BulletExplosion.png", 5, 1, 50.f, 50.f, false,false,this));
		m_DieVFX->SetEntity(this);
	}
	GetAnimationComponent().Play();
}

Bullet::Bullet(const char* texturePath, const int columns, const int rows, bool charged)
	: Projectile(texturePath, columns, rows)
{
	m_IsCharged = charged;
	m_Damage = charged ? 3 : 1;
	m_Pierce = charged ? true : false;
	if(charged)
	{
		m_DieVFX.reset(new VisualEffect("Assets/Games/R-Type/Textures/Player/BulletExplosion.png", 5, 1, 50.f, 50.f, false,false,this));
		m_DieVFX->SetEntity(this);
	}
	GetAnimationComponent().Play();
}

Bullet::Bullet(const char* texturePath, const int columns, const int rows, float posX, float posY, bool charged)
	: Projectile(texturePath, columns, rows)
{
	SetPosX(posX);
	SetPosY(posY);
	m_IsCharged = charged;
	m_Damage = charged ? 3 : 1;
	m_Pierce = charged ? true : false;
	if(charged)
	{
		m_DieVFX.reset(new VisualEffect("Assets/Games/R-Type/Textures/Player/BulletExplosion.png", 5, 1, 50.f, 50.f, false,false,this));
		m_DieVFX->SetEntity(this);
	}
	GetAnimationComponent().Play();
}

void Bullet::Update(float deltaTime)
{
	if(IsExploding())
	{
		m_DieVFX->SetPosX(GetPosition().x + static_cast<float>(GetSize().x) - static_cast<float>(m_DieVFX->GetSprite()->GetWidth()) / 2.f);
		m_DieVFX->Update(deltaTime);
		return;
	}
	
	SetPosX(GetPosition().x + GetMoveSpeed() * deltaTime);
	Animate(deltaTime);

	if(static_cast<int>(GetPosition().x) + GetSize().x > AppConfig::Width)
	{
		SetCanDestroy();
	}
}
