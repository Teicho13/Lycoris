#include "R-Type/Entities/Projectile.h"
#include <iostream>

#include "Core/Sprite.h"

Projectile::Projectile(const char* texturePath)
	:Entity(texturePath)
{
	m_DieVFX.reset(nullptr);
}

Projectile::Projectile(const char* texturePath, const int columns, const int rows)
	:Entity(texturePath, columns,rows)
{
	m_DieVFX.reset(nullptr);
}

float Projectile::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

void Projectile::SetMoveSpeed(float newSpeed)
{
	m_MoveSpeed = newSpeed;
}

void Projectile::Explode()
{
	if(m_DieVFX != nullptr)
	{
		Entity::Explode();
		return;
	}

	SetCanDestroy();
}

int Projectile::GetDamage() const
{
	return m_Damage;
}

bool Projectile::IsPierce() const
{
	return m_Pierce;
}

void Projectile::SetCanDestroy()
{
	m_CanRemove = true;
}

bool Projectile::ShouldRemove() const
{
	return m_CanRemove;
}
