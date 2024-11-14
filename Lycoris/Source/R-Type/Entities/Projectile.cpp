#include "R-Type/Entities/Projectile.h"
#include <iostream>

#include "Core/Sprite.h"

Projectile::Projectile(const char* texturePath)
	:Entity(texturePath)
{
}

Projectile::Projectile(const char* texturePath, const int columns, const int rows)
	:Entity(texturePath, columns,rows)
{
}

float Projectile::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

void Projectile::SetMoveSpeed(float newSpeed)
{
	m_MoveSpeed = newSpeed;
}

void Projectile::SetCanDestroy()
{
	m_CanRemove = true;
}

bool Projectile::ShouldRemove() const
{
	return m_CanRemove;
}
