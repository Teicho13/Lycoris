#include "./Managers/EnemyManager.h"

#include "TextureManager.h"
#include "./Entities/Entity.h"
#include "./R-Type/Entities/Projectile.h"
#include "R-Type/Entities/Enemies/Patapata.h"

#include "Core/Math/Collision.h"
#include "R-Type/Entities/Player.h"

void EnemyManager::Update(float deltaTime)
{
	for (int i = 0; i < m_Enemies.size(); ++i)
	{
		if (m_Enemies[i]->ShouldRemove())
		{
			m_Enemies.erase(m_Enemies.begin() + i);
			i--;
			continue;
		}

		m_Enemies[i]->Update(deltaTime);
	}
}

void EnemyManager::Draw() const
{
	for (const auto& entity : m_Enemies)
	{
		entity->Draw();
		//TextureManager::RenderBox(entity->GetPosition().x,entity->GetPosition().y,entity->GetSize().x,entity->GetSize().y, SDL_Color {0,0,255, 255});
	}
}

bool EnemyManager::CheckBulletCollision(const Projectile* bullet) const
{
	for (const auto& enemy : m_Enemies)
	{
		if(Collision::AABB(bullet->GetPosition(),bullet->GetSize(),enemy->GetPosition(),enemy->GetSize()))
		{
			enemy->SetCanDie();
			return true;
		}
	}
	return false;
}

void EnemyManager::CheckPlayerCollision(Player* player) const
{
	for (const auto& enemy : m_Enemies)
	{
		if(Collision::AABB(player->GetPosition(),player->GetSize(),enemy->GetPosition(),enemy->GetSize()))
		{
			enemy->SetCanDie();
			player->Explode();
			SDL_Delay(50);
		}
	}
}

void EnemyManager::AddEntity(m_EnemyType type, int posX, int posY)
{
	switch (type)
	{
	case m_EnemyType::PataPata:
		AddEntity(std::make_unique<Patapata>("Assets/Games/R-Type/Textures/Enemies/PataPata.png", 6, 1,static_cast<float>(posX * 64), static_cast<float>(posY * 64)));
		break;

	default:
		AddEntity(std::make_unique<Patapata>("Assets/Games/R-Type/Textures/Enemies/PataPata.png", 6, 1, static_cast<float>(posX * 64), static_cast<float>(posY * 64)));
		break;
	}
}

void EnemyManager::AddEntity(std::unique_ptr<Entity> entity)
{
	m_Enemies.push_back(std::move(entity));
}

void EnemyManager::ClearEntities()
{
	m_Enemies.clear();
}
