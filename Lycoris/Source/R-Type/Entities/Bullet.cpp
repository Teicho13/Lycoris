#include "./R-Type/Entities/Bullet.h"
#include "./Core/Utility/AppConfig.h"

Bullet::Bullet(const char* texturePath)
	: Projectile(texturePath)
{
}

Bullet::Bullet(const char* texturePath, const int columns, const int rows)
	: Projectile(texturePath, columns, rows)
{
}

Bullet::Bullet(const char* texturePath, const int columns, const int rows, float posX, float posY)
	: Projectile(texturePath, columns, rows)
{
	SetPosX(posX);
	SetPosY(posY);
}

void Bullet::Update(float deltaTime)
{
	SetPosX(GetPosition().x + GetMoveSpeed() * deltaTime);

	if(static_cast<int>(GetPosition().x) + GetSize().x > AppConfig::Width)
	{
		m_CanRemove = true;
	}
}
