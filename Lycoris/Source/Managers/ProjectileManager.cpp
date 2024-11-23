#include "./Managers/ProjectileManager.h"

#include "TextureManager.h"
#include "./R-Type/Entities/Bullet.h"
#include "./R-Type/Entities/Player.h"

#include "./R-Type/Map/Map.h"
#include "./Managers/EnemyManager.h"

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

//Check if the bullet is out of bounds or hits a tile.
void ProjectileManager::BulletCollisionCheck(const Map& map, const float offsetX) const
{
	for (auto& bullet : m_Projectiles)
	{
		if(bullet->IsExploding()) { continue; }
		
		const int posX = (static_cast<int>(bullet->GetPosition().x + offsetX)) / 64;
		const int posX2 = (static_cast<int>(bullet->GetPosition().x + offsetX) + bullet->GetSize().x) / 64;

		const int posY = static_cast<int>(bullet->GetPosition().y / 64);
		int posY2 = (static_cast<int>(bullet->GetPosition().y) + bullet->GetSize().y) / 64;

		if (posY2 > (Map::m_MapRows - 1))
			posY2 = 11;

		if(map.HasTileCollision(posX, posX2, posY, posY2))
		{
			//bullet->SetCanDestroy();
			bullet->Explode();
		}
	}
}

//Check collision between enemies and bullets
void ProjectileManager::BulletEnemyCheck(const EnemyManager& enemyManager, const float offsetX) const
{
	//For each projectile check if there is collision between it and the enemies
	for (auto& projectile : m_Projectiles)
	{
		if(enemyManager.CheckBulletCollision(projectile.get()))
		{
			//IF enemy is hit, destroy the bullet.
			if(!projectile->IsPierce())
			{
				projectile->SetCanDestroy();
			}
		}
	}
}

void ProjectileManager::Draw() const
{
	for (const auto& projectile : m_Projectiles)
	{
		projectile->Draw();
		//TextureManager::RenderBox(projectile->GetPosition().x,projectile->GetPosition().y, static_cast<float>(projectile->GetSize().x),static_cast<float>(projectile->GetSize().y),SDL_Color {255,0,0,255});
	}
}

void ProjectileManager::ClearProjectiles()
{
	m_Projectiles.clear();
}

void ProjectileManager::AddBullet(Player* player, bool charged)
{
	if(!charged)
	{
		m_Projectiles.push_back(std::make_unique<Bullet>("Assets/Games/R-Type/Textures/Player/Bullet.png", 1, 1,player->GetPosition().x + static_cast<float>(player->GetSize().x),player->GetPosition().y + static_cast<float>(player->GetSize().y) / 2.f));
	}else
	{
		m_Projectiles.push_back(std::make_unique<Bullet>("Assets/Games/R-Type/Textures/Player/BulletCharged.png", 2, 1,player->GetPosition().x + static_cast<float>(player->GetSize().x),player->GetPosition().y + static_cast<float>(player->GetSize().y) / 2.f, true));
	}
}
