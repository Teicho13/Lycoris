#include <SDL_events.h>
#include "Encounter.h"

#include "Core/UI.h"
#include "Core/Utility/AppConfig.h"
#include "Managers/CollisionManager.h"
#include "Managers/SceneManager.h"
#include "Managers/EnemyManager.h"
#include "Managers/ProjectileManager.h"
#include "managers/TextureManager.h"

#include "R-Type/Entities/Player.h"
#include "R-Type/Extras/Star.h"
#include "R-Type/Map/Camera.h"
#include "R-Type/Map/Map.h"


Player* player;
Camera camera;

//Background decoration
Star *g_Stars[50];

Map g_EncounterMap;
EnemyManager g_EnemyManager;
ProjectileManager g_ProjectileManager;
CollisionManager g_CollisionManager;

UI* g_BeamBar;

void Encounter::Init()
{
    //Setup player
    player = new Player("Assets/Games/R-Type/Textures/Player/Player.png",5,1);
    player->SetCamera(&camera);
    player->GetSprite()->SetFrame(2);

    //Create Map and Set enemies
    g_EncounterMap.SetMapSheet("./Assets/Games/R-Type/MapData/Encounter32.csv", "Assets/Games/R-Type/Textures/Maps/Level01Tiles64Transparent.png", 44, 40);
    g_EncounterMap.CreateEnemies("./Assets/Games/R-Type/MapData/Enemies01.csv", g_EnemyManager);

    //Set all references for needed collisions
    g_CollisionManager.SetReferences(&g_ProjectileManager,&g_EnemyManager,player,&g_EncounterMap,&camera);

    //Create a couple background stars
    for (auto& star : g_Stars)
    {
        star = new Star();
    }

    g_BeamBar = new UI("./Assets/Games/R-Type/Textures/UI/BeamBar.png",(AppConfig::Width / 2) - 288,AppConfig::Height - 24);
}

void Encounter::Tick(float dt)
{
    //If the player died we reset the level for now.
    if(!player->IsAlive())
    {
        SDL_Delay(500);
        SceneManager::GetSceneManager()->ChangeScene(std::make_unique<Encounter>());
        return;
    }
    
    player->Update(dt);
    for (auto star : g_Stars)
    {
        star->Update(dt);
    }
    
    //If we are not exploding, Check collisions with the map and move the camera
    if(!player->IsExploding())
    {
        if(player->HandleTileCollision(g_EncounterMap))
        {
            player->ChangeHealth(-1);
            return;
        }
        camera.MoveCamera(dt);
    }
    
    g_CollisionManager.UpdateCollisions();
    g_ProjectileManager.Update(dt);
    g_EnemyManager.Update(dt);
}

void Encounter::Render()
{
    for (auto star : g_Stars)
    {
        star->Draw();
    }
    g_EncounterMap.DrawMap(camera);
    player->Draw();
    g_ProjectileManager.Draw();
    g_EnemyManager.Draw();


    if(g_BeamBar != nullptr)
    {
        g_BeamBar->Draw();
        if(player->DisplayCharge())
        {
            TextureManager::RenderBoxFilled(g_BeamBar->GetPosition().x + 24, g_BeamBar->GetPosition().y + 3,(player->GetCurrentCharge() * 5.28f),18,SDL_Color{64,62,186,255});
        }
    }
}

void Encounter::Destroy()
{
    g_EncounterMap.ClearMap();
    g_EnemyManager.ClearEntities();
    g_ProjectileManager.ClearProjectiles();
    camera.ResetPosition();
    delete player;

    //Reverse for loop to destroy all stars
    for (int i = 50 - 1; i >= 0; --i)
    {
        delete g_Stars[i];
    }
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
                        g_ProjectileManager.AddBullet(player);
                    }
                    else
                    {
                        g_ProjectileManager.AddBullet(player,true);
                    }
                }
            }
            break;
        }
    }
}
