#pragma once
#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(const char* texturePath, bool charged = false);
	Bullet(const char* texturePath, const int columns, const int rows, bool charged = false);
	Bullet(const char* texturePath, const int columns, const int rows, float posX, float posY, bool charged = false);

	void Update(float deltaTime) override;

private:
	bool m_IsCharged = false;
};
