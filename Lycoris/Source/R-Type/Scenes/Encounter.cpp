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

Map g_EncounterMap;
EnemyManager g_EnemyManager;
ProjectileManager g_ProjectileManager;

void Encounter::Init()
{
    //Setup player
    player = new Player("Assets/Games/R-Type/Textures/Player/Player.png",5,1);
    player->SetCamera(&camera);
    player->GetSprite()->SetFrame(2);

    //Create Map and Set enemies
    g_EncounterMap.SetMapSheet("./Assets/Games/R-Type/MapData/Level01.csv", "Assets/Games/R-Type/Textures/Maps/Level01Tiles64.png", 22, 20);
    g_EncounterMap.CreateEnemies("./Assets/Games/R-Type/MapData/Enemies01.csv", g_EnemyManager);
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
        if(player->HandleTileCollision(g_EncounterMap))
        {
            player->Explode();
            SDL_Delay(50);
            return;
        }

        camera.MoveCamera(dt);
    }
	
	
    g_ProjectileManager.Update(dt);
    g_ProjectileManager.BulletCollisionCheck(g_EncounterMap, camera.GetPosX());
    g_ProjectileManager.BulletEnemyCheck(g_EnemyManager, camera.GetPosX());
    g_EnemyManager.Update(dt);
}

void Encounter::Render()
{
    g_EncounterMap.DrawMap(camera);
    player->Draw();
    g_ProjectileManager.Draw();
    g_EnemyManager.Draw();
}

void Encounter::Destroy()
{
    camera.ResetPosition();
    delete player;
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
                        g_ProjectileManager.AddBullet(player);
                    }
                    else
                    {
                        g_ProjectileManager.AddBullet(player);
                    }
                }
            }
            break;
        }
		
    }
}
