#pragma once
#include "Entities/Entity.h"

class Projectile : public Entity
{
public:
	Projectile(const char* texturePath);
	Projectile(const char* texturePath, const int columns, const int rows);

	float GetMoveSpeed() const;
	void SetMoveSpeed(float newSpeed);

	void Explode() override;

	int GetDamage() const;
	bool IsPierce() const;
	
	void SetCanDestroy();
	bool ShouldRemove() const;

protected:
	bool m_CanRemove = false;
	bool m_Pierce = false;
	int m_Damage = 1;
private:
	float m_MoveSpeed = 1000.f;
	
};
