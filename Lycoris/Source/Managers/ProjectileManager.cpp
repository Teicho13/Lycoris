#include "./Managers/ProjectileManager.h"
#include "./R-Type/Entities/Bullet.h"
#include "./R-Type/Entities/Player.h"

#include "./R-Type/Map/Map.h"
#include "./Managers/EnemyManager.h"

ProjectileManager::~ProjectileManager()
{
	ClearProjectiles();
}

void ProjectileManager::Update(float deltaTime)
{
	for (int i = 0; i < m_Projectiles.size(); ++i)
	{
		if(m_Projectiles[i]->ShouldRemove())
		{
			m_Projectiles.erase(m_Projectiles.begin() + i);
			i--;
			continue;
		}

		m_Projectiles[i]->Update(deltaTime);
	}
}

void ProjectileManager::BulletCollisionCheck(const Map& map, const float offsetX) const
{
	for (auto& bullet : m_Projectiles)
	{
		int posX = (static_cast<int>(bullet->GetPosition().x + offsetX)) / 64;
		int posX2 = (static_cast<int>(bullet->GetPosition().x + offsetX) + bullet->GetSize().x) / 64;

		int posY = static_cast<int>(bullet->GetPosition().y / 64);
		int posY2 = (static_cast<int>(bullet->GetPosition().y) + bullet->GetSize().y) / 64;

		if (posY2 > (Map::m_MapRows - 1))
			posY2 = 11;

		if(map.HasTileCollision(posX, posX2, posY, posY2))
		{
			bullet->SetCanDestroy();
		}
	}
}

void ProjectileManager::BulletEnemyCheck(EnemyManager& em, const float offsetX) const
{
	for (auto& element : m_Projectiles)
	{
		if(em.CheckBulletCollision(element.get()))
		{
			element->SetCanDestroy();
		}
	}
}

void ProjectileManager::Draw() const
{
	for (const auto& projectile : m_Projectiles)
	{
		projectile->Draw();
	}
}

void ProjectileManager::ClearProjectiles()
{
	m_Projectiles.clear();
}

void ProjectileManager::AddBullet(Player* player)
{
	m_Projectiles.push_back(std::make_unique<Bullet>("Assets/Games/R-Type/Textures/Player/Bullet.png", 1, 1,player->GetPosition().x + static_cast<float>(player->GetSize().x),player->GetPosition().y + static_cast<float>(player->GetSize().y) / 2.f));
}
