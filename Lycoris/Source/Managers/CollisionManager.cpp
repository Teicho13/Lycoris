#include "CollisionManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"

#include "R-Type/Entities/Player.h"
#include "R-Type/Map/Map.h"
#include "R-Type/Map/Camera.h"

void CollisionManager::SetReferences(ProjectileManager* projectileManager, EnemyManager* enemyManager, Player* player,
    Map* map, Camera* cam)
{
    m_PlayerRef = player;
    m_ProjectileManagerRef = projectileManager;
    m_EnemyManagerRef = enemyManager;
    m_MapRef = map;
    m_CameraRef = cam;
}

void CollisionManager::UpdateCollisions()
{
    m_ProjectileManagerRef->BulletCollisionCheck(*m_MapRef, m_CameraRef->GetPosX());
    m_ProjectileManagerRef->BulletEnemyCheck(*m_EnemyManagerRef, m_CameraRef->GetPosX());
    m_EnemyManagerRef->CheckPlayerCollision(m_PlayerRef);
}
