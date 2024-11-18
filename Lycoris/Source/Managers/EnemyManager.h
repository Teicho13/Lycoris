#pragma once
#include <memory>
#include <vector>

enum class m_EnemyType { PataPata, Blink, Scant, Bug, Cancer, Blaster };

class Player;
class Entity;
class Projectile;
class EnemyManager
{
public:
	EnemyManager() = default;
	~EnemyManager() = default;

	void Update(float deltaTime);
	void Draw() const;

	bool CheckBulletCollision(const Projectile* bullet) const;
	void CheckPlayerCollision(Player* player) const;

	void AddEntity(m_EnemyType type, int posX, int posY);
	void ClearEntities();
private:

	void AddEntity(std::unique_ptr<Entity> entity);

	std::vector<std::unique_ptr<Entity>> m_Enemies;
};
