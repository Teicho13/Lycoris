#pragma once

#include "./Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(const char* texturePath);
	Bullet(const char* texturePath, const int columns, const int rows);
	Bullet(const char* texturePath, const int columns, const int rows, float posX, float posY);

	void Update(float deltaTime) override;
};
