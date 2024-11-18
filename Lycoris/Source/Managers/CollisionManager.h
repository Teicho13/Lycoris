#pragma once

class Camera;
class Map;
class Player;
class EnemyManager;
class ProjectileManager;

class CollisionManager
{
public:
    void SetReferences(ProjectileManager* projectileManager, EnemyManager* enemyManager,Player* player, Map* map, Camera* cam);
    void UpdateCollisions() const;
    
private:
    Player* m_PlayerRef = nullptr;
    ProjectileManager* m_ProjectileManagerRef = nullptr;
    EnemyManager* m_EnemyManagerRef = nullptr;
    Map* m_MapRef = nullptr;
    Camera* m_CameraRef = nullptr;
};
