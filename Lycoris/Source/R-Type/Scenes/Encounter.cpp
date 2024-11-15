#include <SDL_events.h>
#include "Encounter.h"

#include "Managers/SceneManager.h"
#include "Managers/EnemyManager.h"
#include "Managers/ProjectileManager.h"

#include "R-Type/Entities/Player.h"
#include "R-Type/Map/Camera.h"
#include "R-Type/Map/Map.h"


Player* player;
Camera camera;

Map* m_Level01 = nullptr;

EnemyManager enemyManager;
ProjectileManager projectileManager;

void Encounter::Init()
{
    //Setup player
    player = new Player("Assets/Games/R-Type/Textures/Player/Player.png",5,1);
    player->SetCamera(&camera);
    player->GetSprite()->SetFrame(2);

    //Create Map and Set enemies
    m_Level01 = new Map("./Assets/Games/R-Type/MapData/Level01.csv", "Assets/Games/R-Type/Textures/Maps/Level01Tiles64.png", 22, 20);
    m_Level01->CreateEnemies("./Assets/Games/R-Type/MapData/Enemies01.csv", enemyManager);
}

void Encounter::Tick(float dt)
{
    if(!player->IsAlive())
    {
        SceneManager::GetSceneManager()->ChangeScene(std::make_unique<Encounter>());
        return;
    }
    player->Update(dt);
    if(!player->IsExploding())
    {
        if(player->HandleTileCollision(m_Level01))
        {
            player->Explode();
            SDL_Delay(50);
            return;
        }

        camera.MoveCamera(dt);
    }
	
	
    projectileManager.Update(dt);
    projectileManager.BulletCollisionCheck(*m_Level01, camera.GetPosX());
    projectileManager.BulletEnemyCheck(enemyManager, camera.GetPosX());
    enemyManager.Update(dt);
}

void Encounter::Render()
{
    m_Level01->DrawMap(camera);
    player->Draw();
    projectileManager.Draw();
    enemyManager.Draw();
}

void Encounter::Destroy()
{
    projectileManager.ClearProjectiles();
    enemyManager.ClearEntities();
    camera.ResetPosition();
    delete player;
    delete m_Level01;
}

void Encounter::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            //Window "X" is clicked
        case SDL_QUIT:
                SceneManager::GetSceneManager()->Shutdown();
            break;

            //key is pressed
            case SDL_KEYDOWN:
                //If Escape is clicked exit out
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SceneManager::GetSceneManager()->Shutdown();
                    return;
                }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                player->m_InputHeld = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                player->GetSprite()->ChangeTexture("Assets/Games/R-Type/Textures/Player/PlayerAlt.png");
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if(!player->IsExploding())
                {
                    player->m_InputHeld = false;
                    if (!player->FullyCharged())
                    {
                        //TODO: Replace with Charged Bullet type
                        projectileManager.AddBullet(player);
                    }
                    else
                    {
                        projectileManager.AddBullet(player);
                    }
                }
            }
            break;
        }
		
    }
}
