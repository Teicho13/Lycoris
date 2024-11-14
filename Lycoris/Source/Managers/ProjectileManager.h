#pragma once
#include <memory>
#include <vector>

class Projectile;
class Player;
class Map;
class EnemyManager;

class ProjectileManager
{
public:
	ProjectileManager() = default;

	void Update(float deltaTime);
	void BulletCollisionCheck(const Map& map, const float offsetX) const;
	void BulletEnemyCheck(EnemyManager& em, const float offsetX) const;
	void Draw() const;
	void ClearProjectiles();


	void AddBullet(Player* player);

private:
	std::vector<std::unique_ptr<Projectile>> m_Projectiles;
};
