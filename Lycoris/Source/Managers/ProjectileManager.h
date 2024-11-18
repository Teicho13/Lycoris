#pragma once
#include <memory>
#include <vector>
#include "R-Type/Entities/Projectile.h"


class Player;
class Map;
class EnemyManager;

class ProjectileManager
{
public:
	ProjectileManager() = default;
	~ProjectileManager() = default;

	void Update(float deltaTime);
	void BulletCollisionCheck(const Map& map, const float offsetX) const;
	void BulletEnemyCheck(const EnemyManager& enemyManager, const float offsetX) const;
	void Draw() const;
	void ClearProjectiles();


	void AddBullet(Player* player);

private:
	std::vector<std::unique_ptr<Projectile>> m_Projectiles;
};
