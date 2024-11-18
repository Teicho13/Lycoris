#include "./Managers/EnemyManager.h"
#include "./Entities/Entity.h"
#include "./R-Type/Entities/Projectile.h"
#include "R-Type/Entities/Enemies/Patapata.h"

EnemyManager::~EnemyManager()
{
	ClearEntities();
}

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
	}
}

bool EnemyManager::CheckBulletCollision(Projectile* bullet)
{
	for (auto& enemy : m_Enemies)
	{
		//We do a simple AABB
		if (enemy->GetPosition().x + static_cast<float>(enemy->GetSize().x) >= bullet->GetPosition().x &&
			bullet->GetPosition().x + static_cast<float>(bullet->GetSize().x) >= enemy->GetPosition().x &&
			enemy->GetPosition().y + static_cast<float>(enemy->GetSize().y) >= bullet->GetPosition().y &&
			bullet->GetPosition().y + static_cast<float>(bullet->GetSize().y) >= enemy->GetPosition().y)
		{
			enemy->SetCanDie();
			return true;
		}

		return false;
	}

	return false;
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
